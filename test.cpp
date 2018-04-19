#include <iostream>
#include <string>
#include "vini.hpp"

using namespace std;

int main() {
    Vini file("test.ini");

    string output_one = file.get("test", "key", "default");

    cout << output_one << endl;

    string output_two = file.get("test", "secondkey", "defaultvalue");

    cout << output_two << endl;

    string output_three = file.get("anothertest", "othertest", "default");

    cout << output_three << endl;

    file.set("athirdtest", "keyone", "This works!");

    string output_four = file.get("athirdtest", "keyone", "This didn't work!");

    cout << output_four << endl;

    //string output_four = file.save("test_output.ini");

    //cout << output_four << endl;

    return 0;
}