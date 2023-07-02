#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

using namespace std;

int main()
{
    // create a JSON value with different types
    json json_types =
    {
        {"boolean", true},
        {
            "number", {
                {"integer", 42},
                {"floating-point", 17.23}
            }
        },
        {"string", "Hello, world!"},
        {"array", {1, 2, 3, 4, 5}},
        {"null", nullptr}
    };

    // use explicit conversions
    auto v1 = json_types["boolean"].get<bool>();
    auto v2 = json_types["number"]["integer"].get<int>();
    auto v3 = json_types["number"]["integer"].get<short>();
    auto v4 = json_types["number"]["floating-point"].get<float>();
    auto v5 = json_types["number"]["floating-point"].get<int>();
    auto v6 = json_types["string"].get<std::string>();
    auto v7 = json_types["array"].get<std::vector<short>>();
    auto v8 = json_types.get<std::unordered_map<std::string, json>>();

    // use explicit conversions
    json_types["boolean"].get_to(v1);
    json_types["number"]["integer"].get_to(v2);
    json_types["number"]["integer"].get_to(v3);
    json_types["number"]["floating-point"].get_to(v4);
    json_types["number"]["floating-point"].get_to(v5);
    json_types["string"].get_to(v6);
    json_types["array"].get_to(v7);
    json_types.get_to(v8);

    // access element with at or []
    json j1 = json_types.at("number");
    cout << j1["integer"]; // 42
    j1["others"] = "hello";
    // access element with value(key, default value) default value if key non exist.
    auto b1 = json_types.value("boolean", false);
    string v_string = json_types.value("nonexisting", "oops");
    // Unlike at, this function does not throw if the given key/ptr was not found.
    // Unlike operator[], this function does not implicitly add an element to the position defined by key/ptr key.
    // find object element with key
    // Iterator to an element with a key equivalent to key. If no such element is found or the JSON value is not an object, a past-the-end iterator
    auto it_string = json_types.find("string"); // *it_string : Hello, world!

    // check contain key
    cout << json_types.contains("number"); // true


    // read data from file
    ifstream input_file("/mnt/hgfs/ShareData/QtProject/DemoJson/data.json");
    json data = json::parse(input_file);
    std::cout << data["Ben"] << std::endl;
    input_file.close();
    // write data to file
    ofstream out_file("/mnt/hgfs/ShareData/QtProject/DemoJson/data_out.json");
    data["other"] = "new data";
    string temp_string = data.dump(4);
    out_file << temp_string;
    out_file.close();

    return 0;
}
