CURL has several components that work together to perform HTTP requests. One of the key components is the cookie jar. A cookie jar is a collection of cookies that are stored in memory and used for subsequent HTTP requests. 
The following is an example program that uses libcurl's cookies functionality:
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
int main(void) {
CURL *curl;
CURLcode res;
struct curl_slist *cookies;
struct curl_slist *cookies2;
char buffer[1024];
curl = curl_easy_init();
if(!curl) {
fprintf(stderr, "Failed to init!\n");
return 1;
}
curl_easy_setopt(curl, CURLOPT_URL, "https://www.example.com");
curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./cookies.txt");
curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./cookies.txt");
res = curl_easy_perform(curl);
if(res != CURLE_OK) {
fprintf(stderr, "Failed to fetch!\n");
curl_easy_cleanup(curl);
return 1;
}
curl_easy_getinfo(curl, CURLINFO_SET_COOKIELIST, &cookies);
curl_slist_append(cookies, "Cookie1=Value1");
curl_easy_setopt(curl, CURLOPT_COOKIELIST, cookies);
curl_easy_perform(curl);
curl_easy_getinfo(curl, CURLINFO_SET_COOKIELIST, &cookies2);
for(; cookies2; cookies2 = cookies2->next) {
printf("%s\n", cookies2->data);
}
curl_easy_cleanup(curl);
return 0;
}
