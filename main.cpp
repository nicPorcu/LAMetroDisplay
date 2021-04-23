#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <memory>

using namespace std;

namespace {
    size_t callback(
        const char* in,
        size_t size,
        size_t num,
        string* out)
    {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
}

void getLines(){
    std::string agency = "lametro-rail";
    //std::string url = "http://www.wikipedia.org";
    std::string url = "https://api.metro.net/agencies/" +agency+ "/"; 
    
    // Create Curl
    CURL *curl = curl_easy_init();
    if(curl) {
        // Set options: URL, IP Resolve, Timeout, & Redirects
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4); //IPv4
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Response information
        long httpCode(0);

        
        unique_ptr<string> httpData(new string);

        // Data handling function and container
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

        // Run GET, capture resp codem, and clean up
        curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);

        cout << httpCode << endl;

        if(httpCode == 200) {
            cerr << "Sucessful response from " << url << endl;
            Json::Value jsonData;
            Json::Reader jsonReader;

            if(jsonReader.parse(*httpData.get(), jsonData)) {
                cerr << "Sucessfully parsed JSON data" << endl;
                cerr << jsonData << endl;
            }
            //delete httpData.get();
        } else {
            cerr << "Couldn't GET from " << url << endl;
            cerr << httpCode << " error" << endl;
            delete httpData.get();
        }
    } else {
        cerr << "Curl failed" <<endl;
        //delete httpData.get();
        
    }
    //delete httpData.get();
}



int main(int argc, char ** argv){
    //curlpp::Cleanup myCleanup;

    // Send request and get a result.
    // Here I use a shortcut to get it in a string stream ...

    //curlpp::Cleanup myCleanup;

    // Send request and get a result.
    // Here I use a shortcut to get it in a string stream ...

    //std::ostringstream os;
    //os << curlpp::options::Url(std::string("http://www.wikipedia.org"));

    getLines();

    return 0;

}

