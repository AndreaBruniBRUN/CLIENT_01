#include <iostream>
#include <sstream>
#include <curl/curl.h>

int main_2() {
    // Inizializzare la libreria cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);

    CURL* curl = curl_easy_init();
    if (curl) {
        // Creare una stringa JSON con i dati x, y, z
        std::string x = "7766";
        std::string y = "-0.81188965";
        std::string z = "3.7110214";

        std::ostringstream oss;
        oss << "{\"x\": \"" << x << "\", \"y\": \"" << y << "\", \"z\": \"" << z << "\"}";
        std::string jsonData = oss.str();

        // Impostare l'URL del server Node.js
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/receive");

        // Impostare il tipo di contenuto dell'intestazione della richiesta come application/json
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Impostare i dati JSON come corpo della richiesta
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

        // Eseguire la richiesta HTTP
        CURLcode res = curl_easy_perform(curl);

        // Controllare gli errori
        if (res != CURLE_OK) {
            fprintf(stderr, "Errore nella richiesta cURL: %s\n", curl_easy_strerror(res));
        }

        // Chiudere la sessione cURL
        curl_easy_cleanup(curl);

        // Liberare l'intestazione della richiesta
        curl_slist_free_all(headers);
    }

    // Terminare la libreria cURL
    curl_global_cleanup();

    return 0;
}