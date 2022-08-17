#include <iostream>
#include <time.h>
#include <iterator>
#include <algorithm> 
#include <array>
#include <cstdlib>
#include <iomanip>
using namespace std;



bool isInArray(int check[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (check[i] == value) {
            return true;

        }
    }

    return false;
}

void NumBag(int arr[])
{
#define run 90
#define max 90
#define maxNum 90

    cout << "CEKILEN NUMARALAR:" << endl;

    srand(time(NULL));

    int c;
    bool isExist;

    for (int i = 0; i < maxNum; i++) {
        do {

            c = rand() % maxNum + 1;

            isExist = isInArray(arr, maxNum, c);
        } while (isExist == true);

        if (i != 0 && i % 10 == 0) {
            cout << endl;
        }

        arr[i] = c;
        if (c < 10) {
            cout << " ";
        }
        cout << c << " ";


    }

    cout << endl;
}

int lower = 1;
int upper = 90;

void generateCards(int tempCards[][15], int cardCount) {

    for (int i = 0; i < cardCount; i++) {
        int number;
        bool isExist;
        int counter = 0;

        srand(time(NULL) * (i + 1) * 100);

        while (counter < 15) {

            do {

                number = (rand() % (upper - lower + 1)) + lower;

                isExist = std::find(std::begin(tempCards[i]), std::end(tempCards[i]), number) != std::end(tempCards[i]);
            } while (isExist == true);

            tempCards[i][counter] = number;
            counter++;
        }
    }

}

void printCards(int cards[][15], int cardCount) {
    for (int i = 0; i < cardCount; i++) {
        cout << "Kart No" << i << ": ";
        for (int k = 0; k < 15; k++) {
            if (cards[i][k] < 10) {
                cout << " ";
            }
            cout << cards[i][k] << "  ";
        }

        cout << endl;
    }
}

bool checkCard(int num, int card[][15], int user) {
    for (int i = 0; i < 15; i++) {
        if (card[user][i] == num) {
            card[user][i] = -1;
            return true;
        }
    }
    return false;
}

int userPoint(int userCards[][15], int cards[], int userCount, int userState[])
{
    int cinkoSayac, type;
    int nums;
    for (int i = 0; i < 90; i++)
    {
        nums = 0;
        for (int j = 0; j < 15; j++)
        {
            if (cards[userCards[i][j]] == -1)
                nums++;

            if (nums == 5 && cinkoSayac == 0)
            {
                userState[i] += 5;
                cinkoSayac++;
                cout << "1. cinkoyu " << i << " numarali oyuncu yapti." << endl;
                printCards(userCards, userCount);
            }
            else if (nums == 10 && cinkoSayac == 1)
            {
                userState[i] += 10;
                cinkoSayac++;
                cout << "2. cinkoyu " << i << " numarali oyuncu yapti." << endl;
            }
            else if (nums == 15 && cinkoSayac == 2)
            {
                userState[i] += 15;
                cinkoSayac++;
                cout << i << " numarali oyuncu tombala yapti. " << endl;
                printCards(userCards, userCount);
                cout << type << ". set tamamlandi." << endl;
                cout << endl;
            }

        }
    }

    return cinkoSayac;
}


int main() {
    int cards[10][15];
    int generatedNumbers[90];

    //Cinko sayısı
    int cinko = 1;

    cout << "TOMBALA KARTLARI HAZIRLANIYOR ..." << endl;

    generateCards(cards, 10);

    printCards(cards, 10);

    int userCount;

    do {
        cout << endl << "Oyuncu Sayisi: ";
        cin >> userCount;
    } while (userCount < 2 || userCount > 5);

    int userCards[userCount][15];
    int chosenCards[userCount];

    cout << endl << "Oyuncular icin secilen kart numaralari" << endl;

    srand(time(NULL));
    for (int i = 0; i < userCount; i++) {
        int c;
        bool isExist;

        do {

            c = rand() % 10;

            isExist = isInArray(chosenCards, userCount, c);
        } while (isExist == true);

        chosenCards[i] = c;

        for (int k = 0; k < 15; k++) {
            userCards[i][k] = cards[c][k];
        }

        cout << c << " ";
    }

    cout << endl;

    printCards(userCards, userCount);
    cout << endl;

    int numbers[90];
    int userState[userCount];

    for (int i = 0; i < userCount; i++) {
        userState[i] = 0;
    }
    NumBag(numbers);
    cout << endl;

    userPoint(userCards, cards[userCount], userCount, userState);


    for (int i = 0; i < 90; i++) {
        int num = numbers[i];
        if (cinko == 4)
        {
            break;
        }

        for (int k = 0; k < userCount; k++) {
            if (checkCard(num, userCards, k)) {
                userState[k]++;

                if (userState[k] == cinko * 5) {
                    cout << cinko << ". cinkoyu " << k << " numaralı oyuncu kazandi" << endl;
                    printCards(userCards, userCount);
                    cinko++;

                    cout << endl;

                }
            }
        }
    }



    int userPoint[userCount];
    for (int i = 0; i < userCount; i++)
    {
        userPoint[i] = 0;

        for (int k = 0; k < userCount; k++)
        {
            if (userState[k] == 5)
            {
                userPoint[k] += 5;
            }
            else if (userState[k] == 10)
            {
                userPoint[k] += 10;
            }
            else if (userState[k] == 15)
            {
                userPoint[k] += 15;
            }

        }
    }

    return 0;
}

