#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initial size of the array
static int tab_size = 2;

// Structure with data set of each person
typedef struct Person {
    char name[20];
    float amount;
} person_t;

/**
 * @brief Ascending sorting
 *
 * @param arr pointer to person_t structure
 * @param size size of the array
 */
void bubbleSort(person_t *arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j].amount > arr[j + 1].amount) {
                person_t temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief Displaying the data of a particular person
 *
 * @param person pointer to person_t structure
 */
void printPerson(person_t *person) {
    printf("\n%s", person->name);
    printf("\n%f\n", person->amount);
}

/**
 * @brief Introducing another person for settlement
 *
 * @param person pointer to person_t structure
 */
void insertPersonData(person_t *person) {
    printf("\nGive name: ");
    scanf("%19s", person->name);

    printf("\nGive amount: ");
    scanf("%f", &person->amount);

    while (getchar() != '\n');
}

/**
 * @brief Enlargement of the board by a new person
 *
 * @param person pointer to person_t structure
 * @param new_tab_size size of the new array
 * @return pointer to the new array
 */
person_t* addPerson(person_t *person, int new_tab_size) {
    person_t* new_tab = (person_t*)malloc(new_tab_size * sizeof(person_t));

    for(int i = 0; i < new_tab_size - 1; ++i) {
        *(new_tab+i) = *(person+i);
    }

    insertPersonData(&new_tab[new_tab_size - 1]);

    return new_tab;
}

unsigned Init() {
    person_t *tab = (person_t *)malloc(tab_size * sizeof(person_t));

    if (tab == NULL) {
        printf("Memory allocation error\n");
        return 1;
    }

    for(int i = 0; i < tab_size; ++i) {
        insertPersonData(&tab[i]);
    }
    
    while(1) {
        // Adding more people - expanding the array
        char answer[3];
        printf("\nAdd another person? (yes/no): ");
        scanf("%3s", answer);

        if (strcmp(answer, "yes") == 0) {
            tab_size += 1;
            person_t *new_tab = addPerson(tab, tab_size);
            free(tab);
            tab = new_tab;
        } else {
            // Once we have all the people - we sort the board from smallest to largest amount
            bubbleSort(tab, tab_size);

            for(int i = 0; i < tab_size; ++i) {
                printPerson(&tab[i]);
            }

            double sum = 0; 
            double per_person = 0;

            for(int i = 0; i < tab_size; ++i) {
                sum += tab[i].amount;
            }

            per_person = sum / (double)tab_size;

            printf("\nSum: %f\nPer person: %f\n", sum, per_person);

            for(int i = 0; i < tab_size - 1; ++i) {
                float delta = per_person - tab[i].amount;

                if(delta > 0) {
                    printf("\n%s needs to transfer %f to %s\n", tab[i].name, delta, tab[tab_size-1].name);
                    tab[i].amount = tab[i].amount + delta;
                    tab[tab_size-1].amount = tab[tab_size-1].amount - delta;

                } else if(delta < 0) {
                    printf("\n%s needs to transfer %f to %s\n", tab[tab_size-1].name, -delta, tab[i].name);
                    tab[i].amount = tab[i].amount + delta;
                    tab[tab_size-1].amount = tab[tab_size-1].amount - delta;
                }
            }
        
            // Checking that all amounts are aligned
            // for(int i = 0; i < tab_size; ++i) { printPerson(&tab[i]); }
            
            break;
        }
    }

    free(tab);
    return 0;
}

int main() {
    Init();
    return 0;
}
