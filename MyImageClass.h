#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class MyImageClass {
    public:
        vector<vector<int>> imgData;
        string type;
        int height;
        int width;
        int cap; // the highest pixel value
    
    MyImageClass(string filename) {
        cout << "made it in" << endl;
        //fstream imgFile;
        ifstream imgFile;
        try {
            imgFile.open(filename);
        }
        catch (exception& e) {
            cout << "Error: " << e.what() << std::endl;
        }
        cout << "test1" << endl;
        string test;
        getline(imgFile, test, '\n');//this->type);
        cout << "test" << test << endl;

        string line;
        if (type == "P3") {
            getline(imgFile, line); //getting rid of the commented line
            string dims;
            getline(imgFile, dims);
            char* cdims = &dims[0];
            this->height = atoi(strtok(cdims, " "));
            this->width = atoi(strtok(cdims, " "));
            getline(imgFile, line);
            this->cap = stoi(line); //just reusing the cdims variable. could rename it to smth else

            int i = 0;
            vector<int> tmp;
            while (getline(imgFile, line)) {
                ++i;
                tmp.push_back(stoi(line));
                if (i > width) {
                    i = 0;
                    this->imgData.push_back(tmp);
                    tmp.clear();
                }        
            }
        }
        imgFile.close();
    }

    MyImageClass() {
        this->type = "";
        this->height = 0;
        this->width = 0;
        this->cap = 0;
    }
    
    MyImageClass operator+(const MyImageClass& img) {
        MyImageClass newImg;
        int minHeight = 0;
        int minWidth = 0;

        if (this->height <= img.height) {
            minHeight = this->height;
        }
        else {
            minHeight = img.height;
        }

        if (this->width <= img.width) {
            minWidth = this->width;
        }
        else {
            minWidth = img.width;
        }

        vector<int> tmp;
        for (int i = 0; i < minHeight; ++i) {
            for (int j = 0; j < minWidth; ++j) {
                int sum = this->imgData[i][j] + img.imgData[i][j];
                if (sum > this->cap) {
                    sum = cap;
                }
                tmp.push_back(sum);
            }
            newImg.imgData.push_back(tmp);
            tmp.empty();
        }
        return newImg;
    }

    MyImageClass operator-(const MyImageClass& img) {
        MyImageClass newImg;
        int minHeight = 0;
        int minWidth = 0;

        if (this->height <= img.height) {
            minHeight = this->height;
        }
        else {
            minHeight = img.height;
        }

        if (this->width <= img.width) {
            minWidth = this->width;
        }
        else {
            minWidth = img.width;
        }

        vector<int> tmp;
        for (int i = 0; i < minHeight; ++i) {
            for (int j = 0; j < minWidth; ++j) {
                int sum = this->imgData[i][j] - img.imgData[i][j];
                if (sum < 0) {
                    sum = 0;
                }
                tmp.push_back(sum);
            }
            newImg.imgData.push_back(tmp);
            tmp.empty();
        }
        return newImg;
    }

    MyImageClass operator*(float multiplier) {
        MyImageClass newImg;
        vector<int> tmp;
        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                int result = this->imgData[i][j] * multiplier;
                if (result > this->cap) {
                    result = this->cap;
                }
                else if (result < 0) {
                    result = 0;
                }
                tmp.push_back(result);
            }
            newImg.imgData.push_back(tmp);
            tmp.empty();
        }
        return newImg;
    }

    int operator[](int index) {
        if (index == 0) {
            return this->imgData[0][0];
        }
        else {
            int col = index % this->width;
            int row = floor(index / this->height);

            if ((col >= 0 && col < this->width) && (row >= 0 && row < this->height)) {
                return this->imgData[0][0];
            }
            else {
                return -1;
            }
            
        }
        
    }

    bool save(string filepath) {
        fstream newFile;
        try {
            newFile.open(filepath);
        }
        catch (exception& e) {
            cout << "Error: " << e.what() << std::endl;
            return false;
        }
        newFile << this->type << endl;
        newFile << this->width << " " << this->height << endl;

        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; i < this->width; ++j) {
                newFile << this->imgData[i][j] << endl;
            }
        }
        newFile.close();
        return true;
    }

    void gammaCorr(float value) {
        MyImageClass newImg;
        vector<int> tmp;
        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                int result = pow(this->imgData[i][j], value);
                if (result > this->cap) {
                    result = this->cap;
                }
                else if (result < 0) {
                    result = 0;
                }
                tmp.push_back(result);
            }
            newImg.imgData.push_back(tmp);
            tmp.empty();
        }
        this->imgData = newImg.imgData; //shallow copy
    }

};


