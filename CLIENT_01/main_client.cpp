#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <curl/curl.h>

int main() {
    std::ifstream inputFile("D:/template.txt"); // Inserisci il percorso al tuo file di dati
    if (!inputFile.is_open()) {
        std::cerr << "Impossibile aprire il file di dati." << std::endl;
        return 1;
    }

    // Inizializzare la libreria cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);

    CURL* curl = curl_easy_init();
    if (curl) {
        std::string line;
        // Leggere le righe dal file e inviarle al server come JSON
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string x, y, z;
            // Assumendo che il file contenga x, y e z separati da spazi
            if (iss >> x >> y >> z) {
                // Costruire la stringa JSON
                //std::ostringstream oss;
  
                double xValue = std::stod(x);
                double yValue = std::stod(y);
                double zValue = std::stod(z);
                //double x = 1;
                //double y = 2;
                //double z = 3;
                //std::string command = "curl --insecure -X POST -H \"Content-Type: application/json\" -d \"{\\\"x\\\": 1.4555, \\\"y\\\": 2.34333, \\\"z\\\": 3.67888}\" https://127.0.0.1:44443/receive"; //forma corretta
                std::ostringstream oss;
                //oss << "curl --insecure -X POST -H \"Content-Type: application/json\" -d \"{\\\"x\\\": " << x << ", \\\"y\\\": " << y << ", \\\"z\\\": " << z << "}\" https://192.168.1.12:443/receive"; //ok streaming   funzionante
                oss << "curl --insecure -X POST -H \"Content-Type: application/json\" -d \"{\\\"x\\\": " << x << ", \\\"y\\\": " << y << ", \\\"z\\\": " << z << "}\" https://127.0.0.1:4443/receive"; //ok streaming   funzionante
                std::string command = oss.str();

                // Esegui il comando curl utilizzando system()
                int exitCode = system(command.c_str());
                // Controlla il codice di uscita
                if (exitCode == 0) {
                    std::cout << "Dati inviati con successo: x=" << x << ", y=" << y << ", z=" << z << std::endl;
                }
                else {
                    std::cerr << "Errore nell'esecuzione del comando curl." << std::endl;
                }

                //std::cout << "jsonData: " << jsonData << std::endl;
                //system("pause");

                // Eseguire la richiesta cURL utilizzando system()
                int result = system(command.c_str());

                // Controllare il risultato dell'esecuzione del comando
                if (result != 0) {
                    std::cerr << "Errore nell'esecuzione della richiesta cURL." << std::endl;
                }

                // Aspettare 1 secondo prima di inviare la prossima richiesta
                //std::this_thread::sleep_for(std::chrono::seconds(1));
                //std::this_thread::sleep_for(std::chrono::milliseconds(250));

            }
            else {
                std::cerr << "Errore nella lettura dei dati dalla riga: " << line << std::endl;
            }
        }

        // Chiudere la sessione cURL
        curl_easy_cleanup(curl);
    }

    // Chiudere il file
    inputFile.close();

    // Terminare la libreria cURL
    curl_global_cleanup();

    return 0;
}





