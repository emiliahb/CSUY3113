#include <iostream>
#include <exception>

#include "MyImageClass.h"

int main(int argc, char* argv[]) {

    try {
        MyImageClass image1("Mandrill.ppm");
        MyImageClass image2("tandon_stacked_color.ppm");
        MyImageClass add;
        MyImageClass subtract;
        MyImageClass multiply;
        
        cout << "Starting addition" << endl;
        add = image1 + image2;
        add.save("addition.ppm");
        cout << "Addition saved" << endl;

        cout << "Starting subtraction" << endl;
        subtract = image1 - image2;
        subtract.save("subtraction.ppm");
        cout << "Subtraction saved" << endl;

        cout << "Starting +=" << endl;
        image1 += image2;
        image1.save("plusequals.ppm");
        cout << "+= saved" << endl;

        MyImageClass image3("Mandrill.ppm");
        cout << "Starting -=" << endl;
        image3 -= image2;
        image3.save("minusequals.ppm");
        cout << "-= saved" << endl;

        MyImageClass image4("Mandrill.ppm");
        cout << "Starting gamma correction" << endl;
        image4.gammaCorr(1.2);
        image4.save("gamma.ppm");
        cout << "Gamma correction saved" << endl;


        /*MyImageClass green;
        green.type = "P3";
        green.width = 4;
        green.height = 4;
        green.cap = 255;

        cout << "HI" << endl;

        vector<vector<vector<int>>> test;
        vector<vector<int>> line;
        vector<int> rgb;
        vector<int> color = {0, 255, 0};
        for (int i = 0; i < green.height; ++i) {
            for (int j = 0; j < green.width; ++j) {
                for (int k = 0; k < 3; ++k) {
                    rgb.push_back(color[k]);
                }
                line.push_back(rgb);
                rgb.clear();
            }
            green.imgData.push_back(line);
            line.clear();
        }
        green.save("green.ppm");*/

    }
    catch (exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}