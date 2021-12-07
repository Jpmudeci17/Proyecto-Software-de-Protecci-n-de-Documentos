#include <iostream>
#include <iomanip>
#include "sodium.h"
#include <fstream>
#include <string>
using namespace std;




int main()
{
       
    int option;
    cout << "Hola seleciona una opcion para continuar";
    std::cout << std::endl;
    cout << "1: Cifrado de Archivos";
    std::cout << std::endl;
    cout << "2: Descifrado de Archivos";
    std::cout << std::endl;
    cout << "3: Generacion y Recuperación de Claves";
    std::cout << std::endl;
    cout << "4: Firma de Archivos";
    std::cout << std::endl;
    cout << "5: Verificacion de Firma de Archivos";
    std::cout << std::endl;
    cout << "0: salir";
    std::cout << std::endl;
    cin >> option;




    if (sodium_init() < 0) {
        /* panic! the library couldn't be initialized, it is not safe to use */
        return -1;
    }

    //lectura del mensaje
    //std::ifstream inFile;
    //inFile.open("C:\\1MB.txt");
   // string sum;
    //string x;
    //if (!inFile) {
        //std::cout << "Unable to open file";
    //    exit(1);
    //}

    //while (inFile >> x) {
    //    sum = sum + " " + x;
    //}

    //inFile.close();
    //unsigned char cat[150];
    //strcpy((char*)cat, sum.c_str());

    unsigned char* cat = new unsigned char[102400];
    int plaintext_len = strlen((char*)cat);

    unsigned char* ciphertext = new unsigned char[plaintext_len];
    unsigned char* deciphertext = new unsigned char[plaintext_len];

    unsigned char key[crypto_stream_chacha20_KEYBYTES];
    unsigned char nonc[crypto_stream_chacha20_NONCEBYTES];

    crypto_secretbox_keygen(key);
    randombytes_buf(nonc, sizeof nonc);


    unsigned char pk[crypto_sign_PUBLICKEYBYTES];
    unsigned char sk[crypto_sign_SECRETKEYBYTES];
    unsigned char sig[crypto_sign_BYTES];



    while (option != 0) {

        if (option == 1) {

            //PEQUEÑO MODULO PARA ABRIR ARCHIVOS
            char archivo[100];
            cout << "Hola seleciona un txt para codificar";
            cin >> archivo;
            string ruta = "D:\\ITESO\\Septimo\\SEGURIDAD EN REDES\\";
            ruta.append(archivo);
            ifstream File(ruta);
            if (File.is_open()) {
                File.getline((char*)cat, 10240, '\0');

                File.close();
            }

            

            
            //codificacion de texto
            
            std::cout << std::endl;
            cout << "Texto Codificado";
            std::cout << std::endl;
            std::cout << std::endl;

            int errorcode = crypto_stream_chacha20_xor(ciphertext, cat, plaintext_len, nonc, key);
            for (int i = 0; i < plaintext_len; i++) {
                std::cout << std::setfill('0') << std::setw(2) << std::hex << int(ciphertext[i]);
            }
            std::cout << std::endl;
            std::cout << std::endl;
        }
        else if (option == 2) {

            std::cout << std::endl;
            cout << "Texto Decodificado";
            std::cout << std::endl;
            std::cout << std::endl;

            int errorcode = crypto_stream_chacha20_xor(deciphertext, ciphertext, plaintext_len, nonc, key);
            for (int i = 0; i < plaintext_len; i++) {
                //std::cout << std::setfill('0') << std::setw(2) << std::hex << int(deciphertext[i]);
            }
            std:cout << deciphertext;
            std::cout << std::endl;
            std::cout << std::endl;
        }
        else if (option == 3) {
            //Generación y Recuperación de Claves hacia o desde 1 archivo

            std::cout << std::endl;
            cout << "Claves generadas";
            std::cout << std::endl;
            cout << "PK";
            std::cout << std::endl;
            std::cout << pk;
            std::cout << std::endl;
            cout << "SK";
            std::cout << std::endl;
            std::cout << sk;


            crypto_sign_keypair(pk, sk);

        }
        else if (option == 4) {
            //Firma de Archivos
            std::cout << std::endl;
            cout << "Archivo Firmado";
            std::cout << std::endl;
            crypto_sign_keypair(pk, sk);
        }
        else if (option == 5) {         
             //Verificación de Firma de Archivos
            crypto_sign_detached(sig, NULL, cat, plaintext_len, sk);
            std::cout << std::endl;

            if (crypto_sign_verify_detached(sig, cat, plaintext_len, pk) != 0) {
                /* Incorrect signature! */

                cout << "Problema con  la Verificación";
            }
            else {
                cout << "Verificacion correcta";
            }
            std::cout << std::endl;

        }
        else {
            cout << "Opcion invalida";
            std::cout << std::endl;

        }

        std::cout << std::endl;
        cout << "Hola seleciona una opcion para continuar";
        std::cout << std::endl;
        cout << "1: Generacion y Recuperación de Claves";
        std::cout << std::endl;
        cout << "2: Cifrado y Descifrado de Archivos";
        std::cout << std::endl;
        cout << "3: Firma de Archivos";
        std::cout << std::endl;
        cout << "4: Verificación de Firma de Archivos";
        std::cout << std::endl;
        cout << "0: salir";
        std::cout << std::endl;
        cin >> option;




    }

    return 0;
}