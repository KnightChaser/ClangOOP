#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    struct Person *this;                                        // this pointer
    
    char name[100];
    char position[100];
    char email[100];
    
    void (*selfIntroduce)(const struct Person *this);
    void (*updatePersonalInformation)(struct Person *this, 
                                      const char *updatedName, 
                                      const char *updatedPosition, 
                                      const char *updatedEmail);
    
} Person;

Person *newPerson(const char *registeredName,
                  const char *registeredPosition,
                  const char *registeredEmail);                 // constructor
void deletePerson(struct Person *personPtr);                    // destructor
void selfIntroduce(const struct Person *this);                  // internal(member) function
void updatePersonalInformation(struct Person *this, 
                               const char *updatedName,
                               const char *updatedPosition,
                               const char *updatedEmail);       // internal(member) function
            

Person *newPerson(const char *registeredName, 
                  const char *registeredPosition, 
                  const char *registeredEmail) {
                      
    Person *internalPersonObject = (Person *)malloc(sizeof(Person));
    
    if (internalPersonObject != NULL) {
        // member variables
        strncpy(internalPersonObject->name, registeredName, sizeof(internalPersonObject->name));
        strncpy(internalPersonObject->position, registeredPosition, sizeof(internalPersonObject->position));
        strncpy(internalPersonObject->email, registeredEmail, sizeof(internalPersonObject->email));
        
        // member functions(function pointers)
        internalPersonObject->this = internalPersonObject;
        internalPersonObject->selfIntroduce = selfIntroduce;
        internalPersonObject->updatePersonalInformation = updatePersonalInformation;
    } else {
        printf("Memory allocation failed during allocating internalPersonObject in Person *newPerson().\n");
        return NULL;
    }
    
    return internalPersonObject;  // Return the created Person object.
}

void deletePerson(struct Person *personPtr) {
    free(personPtr);
}

void selfIntroduce(const struct Person *this) {
    printf("Hello! My name is %s whose job is %s. You can contact me to %s.\n",
            this->name, this->position, this->email);
}

void updatePersonalInformation(struct Person *this, const char *updatedName, const char *updatedPosition, const char *updatedEmail) {
    if (updatedName != NULL)
        strncpy(this->name, updatedName, sizeof(this->name));
    if (updatedPosition != NULL)
        strncpy(this->position, updatedPosition, sizeof(this->position));
    if (updatedEmail != NULL)
        strncpy(this->email, updatedEmail, sizeof(this->email));
}

int main(void) {
    Person *personA = newPerson("Lee Garam", "hacker", "knightchaser@hacker.one");
    
    if (personA != NULL) {
        personA->selfIntroduce(personA->this);
        personA->updatePersonalInformation(personA->this, NULL, "Pro hacker", "knightchaser@hackclub.gachon.ac.kr");
        personA->selfIntroduce(personA->this);
    
        deletePerson(personA);  // Added a semicolon at the end.
    } else {
        printf("Memory allocation for the Person object failed.\n");
    }
    
    return 0;
}

// [Result]
// Hello! My name is Lee Garam whose job is hacker. You can contact me to knightchaser@hacker.one.
// Hello! My name is Lee Garam whose job is Pro hacker. You can contact me to knightchaser@hackclub.gachon.ac.kr.
