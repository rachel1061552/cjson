#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cJSON.h"
#include <string>
#include<iostream>
#include<fstream>
#include <vector>
using namespace std;
#pragma warning(disable : 4996)
vector<string> splitStr2Vec(string s, string splitSep)
{
    vector<string> result;
    int current = 0; //最初由 0 的位置開始找
    int next = 0;
    while (next != -1)
    {
        next = s.find_first_of(splitSep, current); //尋找從current開始，出現splitSep的第一個位置(找不到則回傳-1)
        if (next != current)
        {
            string tmp = s.substr(current, next - current);
            if (!tmp.empty())  //忽略空字串(若不寫的話，尾巴都是分割符會錯)
            {
                result.push_back(tmp);
            }
        }
        current = next + 1; //下次由 next + 1 的位置開始找起。
    }
    return result;
}
int main(int argc, char** argv)
{
    std::fstream file;
    file.open("json_example.json", ios::in);
    char s[100];
    file.read(s, sizeof(s));
    //char s[100] = "{\"boy\":{\"name\":\"Jack\"},\"girls\":[{\"name\":\"Zoe\"},{\"name\":\"Marry\"}],\"unknow\":\"null\"}";
    cJSON* root = cJSON_Parse(s);
    if (!root) {
        printf("get root faild !\n");
        return -1;
    }
    char key[3][20] = { "boy","girls","unknow" };
    char second_key[1][20] = { "name" };

    std::string input;

    while (std::cin >> input) {
        vector<string> sep= splitStr2Vec(input, ">");
        //boy
        if (sep[0] == key[0]) {
            cJSON* js_boy = cJSON_GetObjectItem(root, key[0]);
            if (!js_boy) {
                printf("no boy!\n");
                return -1;
            }
            int array_size = cJSON_GetArraySize(js_boy);
            if (array_size == 0) {
                printf("%s\n", js_boy->valuestring);
            }
            cJSON* item, * it, * js_name;
            int i;
            char* p = NULL;
            if (array_size == 1) {
                if (sep[1] == second_key[0]) {
                    cJSON* name = cJSON_GetObjectItem(js_boy, second_key[0]);
                    if (!name) {
                        printf("No name !\n");
                        return -1;
                    }
                    //printf("name type is %d\n", name->type);
                    printf("%s\n", name->valuestring);
                }
            }
            else {
                for (i = 0; i < array_size; i++) {
                    if (sep[1] == second_key[0]) {
                        item = cJSON_GetArrayItem(js_boy, i);
                        if (!item) {
                            //TODO...
                        }
                        p = cJSON_PrintUnformatted(item);
                        it = cJSON_Parse(p);
                        if (!it)
                            continue;
                        js_name = cJSON_GetObjectItem(it, second_key[0]);
                        printf("%s\n", js_name->valuestring);
                    }
                }
            }
            
        }
        //girls
        if (sep[0] == key[1]) {
            cJSON* js_girls = cJSON_GetObjectItem(root, key[1]);
            if (!js_girls) {
                printf("no girls!\n");
                return -1;
            }
            //printf("girls->");

            int array_size = cJSON_GetArraySize(js_girls);
            if (array_size == 0) {
                printf("%s\n", js_girls->valuestring);
            }
            cJSON* item, * it, * js_name;
            int i;
            char* p = NULL;
            if (array_size == 1) {
                if (sep[1] == second_key[0]) {
                    cJSON* name = cJSON_GetObjectItem(js_girls, second_key[0]);
                    if (!name) {
                        printf("No name !\n");
                        return -1;
                    }
                    //printf("name type is %d\n", name->type);
                    printf("%s\n", name->valuestring);
                }
            }
            else {
                for (i = 0; i < array_size; i++) {
                    if (sep[1] == second_key[0]) {
                        item = cJSON_GetArrayItem(js_girls, i);
                        if (!item) {
                            //TODO...
                        }
                        p = cJSON_PrintUnformatted(item);
                        it = cJSON_Parse(p);
                        if (!it)
                            continue;
                        js_name = cJSON_GetObjectItem(it, second_key[0]);
                        printf("%s\n", js_name->valuestring);
                    }
                }
            }
        }
        //unknow
        if (sep[0] == key[2]) {
            cJSON* js_unknow = cJSON_GetObjectItem(root, key[2]);
            int array_size = cJSON_GetArraySize(js_unknow);
            if (array_size == 0) {
                printf("%s\n", js_unknow->valuestring);
            }
            cJSON* item, * it, * js_name;
            int i;
            char* p = NULL;
            if (array_size == 1) {
                if (sep[1] == second_key[0]) {
                    cJSON* name = cJSON_GetObjectItem(js_unknow, second_key[0]);
                    if (!name) {
                        printf("No name !\n");
                        return -1;
                    }
                    //printf("name type is %d\n", name->type);
                    printf("%s\n", name->valuestring);
                }
            }
            else {
                for (i = 0; i < array_size; i++) {
                    if (sep[1] == second_key[0]) {
                        item = cJSON_GetArrayItem(js_unknow, i);
                        if (!item) {
                            //TODO...
                        }
                        p = cJSON_PrintUnformatted(item);
                        it = cJSON_Parse(p);
                        if (!it)
                            continue;
                        js_name = cJSON_GetObjectItem(it, second_key[0]);
                        printf("%s\n", js_name->valuestring);
                    }
                }
            }
        }
    }
    if (root)
        cJSON_Delete(root);
    return 0;
}