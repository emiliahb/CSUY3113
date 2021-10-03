#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class MyImageClass {
    public:
        vector<vector<vector<int>>> imgData; //a 2D vector where each element is a 3-item long vector that holds values for that pixel's r, g, b values
        string type;
        int height;
        int width;
        int cap; // the highest pixel value
    
    MyImageClass(string filename) {
        ifstream imgFile;
        try {
            imgFile.open(filename);
        }
        catch (exception& e) {
            cout << "Error: " << e.what() << std::endl;
        }
        getline(imgFile, this->type);

        string line;
        string dims;

        getline(imgFile, line); //pulling the next line from the file, checking if it's a comment or not

        if (line[0] == '#') {
            getline(imgFile, dims);
        }
        else {
            dims = line;
        }
            
        char* cdims = &dims[0];
        this->height = atoi(strtok(cdims, " "));
        this->width = atoi(strtok(cdims, " "));
        getline(imgFile, line);
        this->cap = stoi(line);

        //failed attempts at trying to do something with the P6 files
        /*if (type == "P6") {
            imgFile.close();
            imgFile.open(filename, ios::binary);
        }*/
        /*if (this->type == "P6") {
            int size = this->height * this->width * 3;
            char* ptr = new char[size];
            imgFile.read(ptr, size);
            cout << ptr << endl;
        }*/

        int i = 0;
        vector<vector<int>> tmp;
        vector<int> tmppx;

        //reading through the file and creating the image data structure
        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                string px;
                for (int k = 0; k < 3; ++k) {                    
                    getline(imgFile, px);
                    tmppx.push_back(stoi(px));
                }
                tmp.push_back(tmppx);
                tmppx.clear();
            }
            this->imgData.push_back(tmp);
            tmp.clear();
        }
        
        imgFile.close();
    }

    //constructor for when no filename is given to load in
    MyImageClass() {
        this->type = "";
        this->height = 0;
        this->width = 0;
        this->cap = 0;
    }

    MyImageClass operator+=(const MyImageClass& img) {
        MyImageClass newImg;
        int minHeight = 0;
        int minWidth = 0;

        minHeight = (this->height <= img.height) ? this->height : img.height;
        minWidth = (this->width <= img.width) ? this->width : img.width;

        vector<vector<int>> tmp;
        vector<int> tmppx;
        //reading through the entire 2D vector array
        for (int i = 0; i < minHeight; ++i) {
            for (int j = 0; j < minWidth; ++j) {
                for (int k = 0; k < 3; ++k) {
                    //take the values for either r, g, or b, average them, cap them if necessary, add to the new vector
                    int sum = this->imgData[i][j][k] + img.imgData[i][j][k];
                    int avg = sum / 2;
                    if (avg > this->cap) {
                        avg = cap;
                    }
                    tmppx.push_back(avg);
                }
                tmp.push_back(tmppx);
                tmppx.clear();
            }
            newImg.imgData.push_back(tmp);
            tmp.clear();
        }

        this->imgData = newImg.imgData;
        return *this;
    }


    MyImageClass operator+(const MyImageClass& img) {
        MyImageClass newImg;
        int minHeight = 0;
        int minWidth = 0;

        minHeight = (this->height <= img.height) ? this->height : img.height;

        minWidth = (this->width <= img.width) ? this->width : img.width;

        vector<vector<int>> tmp;
        vector<int> tmppx;
        //read through the entire 2D vector
        for (int i = 0; i < minHeight; ++i) {
            for (int j = 0; j < minWidth; ++j) {
                for (int k = 0; k < 3; ++k) {
                    //take the sum of the r, g, or b values and cap if necessary
                    int sum = this->imgData[i][j][k] + img.imgData[i][j][k];
                    if (sum > this->cap) {
                        sum = cap;
                    }
                    tmppx.push_back(sum);
                }
                tmp.push_back(tmppx);
                tmppx.clear();
            }
            newImg.imgData.push_back(tmp);
            tmp.clear();
        }

        newImg.height = minHeight;
        newImg.width = minWidth;
        newImg.cap = this->cap;
        newImg.type = this->type;
        return newImg;
    }

    MyImageClass operator-=(const MyImageClass& img) {
        MyImageClass newImg;
        //x -= y is equivalent to saying x = x - y, so i use the overloaded - operator to write this equivalency
        newImg = *this - img;

        this->imgData = newImg.imgData;
        return *this;
    }

    MyImageClass operator-(const MyImageClass& img) {
        MyImageClass newImg;
        int minHeight = 0;
        int minWidth = 0;

        minHeight = (this->height <= img.height) ? this->height : img.height;

        minWidth = (this->width <= img.width) ? this->width : img.width;

        vector<vector<int>> tmp;
        vector<int> tmppx;
        //read through the entire 2D vector
        for (int i = 0; i < minHeight; ++i) {
            for (int j = 0; j < minWidth; ++j) {
                for (int k = 0; k < 3; ++k) {
                    //subtract respective values, if result is negative then cap at 0
                    int sum = this->imgData[i][j][k] - img.imgData[i][j][k];
                    if (sum < 0) {
                        sum = 0;
                    }
                    tmppx.push_back(sum);
                }
                tmp.push_back(tmppx);
                tmppx.clear();
            }
            newImg.imgData.push_back(tmp);
            tmp.clear();
        }

        newImg.height = minHeight;
        newImg.width = minWidth;
        newImg.cap = this->cap;
        newImg.type = this->type;
        return newImg;
    }

    MyImageClass operator*(float multiplier) {
        MyImageClass newImg;
        vector<int> tmp;
        newImg = *this;
        if (multiplier == 1) {
            return *this;
        }
        else if (multiplier == 0) {
            //if the multiplier is 0, every rgb value should be 0, so i just subtract this from itself to zero out the imgData
            return (*this - *this);
        }
        else {
            for (int i = 0; i < (multiplier - 1); ++i) {
                newImg += *this;
            }
        }
        
        return newImg;
    }

    vector<int> operator[](int index) {
        if (index == 0) {
            return this->imgData[0][0];
        }
        else {
            //calculate the column and row that correspond to the pixel index
            int col = index % this->width;
            int row = floor(index / this->height);

            if ((col >= 0 && col < this->width) && (row >= 0 && row < this->height)) {
                return this->imgData[0][0];
            }
            else {
                return {};
            }
        }
    }

    void mirrorX() {
        vector<vector<vector<int>>> newImgData;
        vector<vector<int>> line;
        vector<int> rgb;

        for (int i = 0; i < this->height; ++i) {
            for (int j = (this->width - 1); j >= 0; --j) {
                for (int k = 0; k < 3; ++k) {
                    rgb.push_back(imgData[i][j][k]);
                }
                line.push_back(rgb);
                rgb.clear();
            }
            newImgData.push_back(line);
            line.clear();
        }

        this->imgData = newImgData;
    }

    bool save(string filepath) {
        ofstream newFile;
        try {
            if (this->type == "P3") {
                newFile.open(filepath);
            }
            /*else if (this->type == "P6") {
                newFile.open(filepath, ios::binary);
                cout << "opened" << endl;
            }*/
        }
        catch (exception& e) {
            cout << "Error: " << e.what() << std::endl;
            return false;
        }

        newFile << this->type << endl;
        newFile << this->width << " " << this->height << endl;
        newFile << this->cap << endl;

        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                for (int k = 0; k < 3; ++k) {
                    newFile << this->imgData[i][j][k] << endl;
                }
            }
        }
        newFile.close();
        return true;
    }

   void gammaCorr(float value) {
        MyImageClass newImg;
        
        vector<vector<int>> tmp;
        vector<int> pxtmp;
        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int result = pow(this->imgData[i][j][k], value);
                    if (result > this->cap) {
                        result = this->cap;
                    }
                    else if (result < 0) {
                        result = 0;
                    }
                    pxtmp.push_back(result);
                }
                tmp.push_back(pxtmp);
                pxtmp.clear();
            }
            newImg.imgData.push_back(tmp);
            tmp.clear();
        }
        this->imgData = newImg.imgData; //shallow copy
    }

};


