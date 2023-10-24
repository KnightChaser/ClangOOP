#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------------ class Person --------------------------------
typedef struct Person {
    struct Person *this; // this pointer

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
                  const char *registeredEmail); // constructor
void deletePerson(struct Person *personPtr);    // destructor
void selfIntroduce(const struct Person *this);   // internal(member) function
void updatePersonalInformation(struct Person *this,
                               const char *updatedName,
                               const char *updatedPosition,
                               const char *updatedEmail); // internal(member) function

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
    printf("Hello! My name is %s whose job is %s. You can contact me at %s.\n",
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
// ------------------------------ class Person (end) --------------------------------

// --------------- class personExtended (Inherited from class Person) ---------------
typedef struct PersonExtended {

    // Inherited struct-based class Person
    Person person;

    struct PersonExtended *this;

    char blogURL[256];
    char ID[32];

    void (*selfIntroduceExtended)(const struct PersonExtended *this);
    void (*updatePersonalInformationExtended)(struct PersonExtended *this,      
                                              const char *updatedName,
                                              const char *updatedPosition,
                                              const char *updatedEmail,
                                              const char *updatedBlogURL,
                                              const char *updatedID);

} PersonExtended;

PersonExtended *newExtendedPerson(const char *registeredName,               // constructor
                                  const char *registeredPosition,
                                  const char *registeredEmail,
                                  const char *registeredBlogURL,
                                  const char *registeredID);   
void selfIntroduceExtended(const struct PersonExtended *this);              // member functions of class PersonExtended
void updatePersonalInformationExtended(struct PersonExtended *this,         // member functions of class PersonExtended
                                       const char *updatedName,
                                       const char *updatedPosition,
                                       const char *updatedEmail,
                                       const char *updatedBlogURL,
                                       const char *updatedID);
void deletePersonExtended(struct PersonExtended *personExtendedPtr);        // destructor

// constructor
PersonExtended *newExtendedPerson(const char *registeredName,
                                  const char *registeredPosition,
                                  const char *registeredEmail,
                                  const char *registeredBlogURL,
                                  const char *registeredID) {

    PersonExtended *internalExtendedPersonObject = (PersonExtended *)malloc(sizeof(PersonExtended));
    if (internalExtendedPersonObject != NULL) {

        // Initialize the inherited Person object
        internalExtendedPersonObject->person = *newPerson(registeredName, registeredPosition, registeredEmail);

        // member variables
        strncpy(internalExtendedPersonObject->blogURL, registeredBlogURL, sizeof(internalExtendedPersonObject->blogURL));
        strncpy(internalExtendedPersonObject->ID, registeredID, sizeof(internalExtendedPersonObject->ID));

        // member functions
        internalExtendedPersonObject->this = internalExtendedPersonObject; // this pointer
        internalExtendedPersonObject->selfIntroduceExtended = selfIntroduceExtended;
        internalExtendedPersonObject->updatePersonalInformationExtended = updatePersonalInformationExtended;

    } else {
        printf("Memory allocation failed while creating newExtendedPerson() in newExtendedPerson()\n");
        return NULL;
    }

    return internalExtendedPersonObject;
}

void selfIntroduceExtended(const struct PersonExtended *this) {
    printf("(Extended) Hello! My name is %s whose job is %s. You can contact me either %s or %s and my personal ID is %s.\n",
            this->person.name,          // from the parent class (Person)
            this->person.position,      // from the parent class (Person)
            this->person.email,         // from the parent class (Person)
            this->blogURL,              // from the current class (PersonExtended)
            this->ID);                  // from the current class (PersonExtended)
}

void updatePersonalInformationExtended(struct PersonExtended *this,         // member functions of class PersonExtended
                                       const char *updatedName,
                                       const char *updatedPosition,
                                       const char *updatedEmail,
                                       const char *updatedBlogURL,
                                       const char *updatedID) {
    
    // delegate possible workload to the parent                                       
    this->person.updatePersonalInformation(&(this->person), updatedName, updatedPosition, updatedEmail);
    
    if (updatedBlogURL != NULL)
        strncpy(this->blogURL, updatedBlogURL, sizeof(this->blogURL));
    if (updatedID != NULL)
        strncpy(this->ID, updatedID, sizeof(this->ID));
}

void deletePersonExtended(struct PersonExtended *personExtendedPtr) {
    free(personExtendedPtr);
}


// ------------ class extendedPerson (end) (Inherited from class Person) ------------

int main(void) {
    Person *jaclyn = newPerson("Jaclyn", "system enginner", "jaclyn@jupyter.com");

    if (jaclyn != NULL) {
        jaclyn->selfIntroduce(jaclyn->this);
        jaclyn->updatePersonalInformation(jaclyn->this, NULL, "Senior system enginner", "jaclyn@engr.internal.jupyter.com");
        jaclyn->selfIntroduce(jaclyn->this);      // check after updating in-object information
        
        deletePerson(jaclyn);
    } else {
        printf("Memory allocation for the Person object failed.\n");
    }
    
    printf("\n");
    
    PersonExtended *knightchaser = newExtendedPerson("Lee Garam", "hacker", "knightchaser@hackclub.gcc.ac.kr", "blog.naver.com/luexr", "17AZX31");

    if (knightchaser != NULL) {
        knightchaser->selfIntroduceExtended(knightchaser->this);
        knightchaser->updatePersonalInformationExtended(knightchaser->this, NULL, "pro hacker", "knightchaser@hacker.one", NULL, "17AZX32");
        knightchaser->selfIntroduceExtended(knightchaser->this);      // check after updating in-object information
        
        deletePersonExtended(knightchaser);
    } else {
        printf("Memory allocation for the PersonExtended object failed.\n");
    }

    return 0;
}

// Hello! My name is Jaclyn whose job is system enginner. You can contact me at jaclyn@jupyter.com.
// Hello! My name is Jaclyn whose job is Senior system enginner. You can contact me at jaclyn@engr.internal.jupyter.com.

// (Extended) Hello! My name is Lee Garam whose job is hacker. You can contact me either knightchaser@hackclub.gcc.ac.kr or blog.naver.com/luexr and my personal ID is 17AZX31.
// (Extended) Hello! My name is Lee Garam whose job is pro hacker. You can contact me either knightchaser@hacker.one or blog.naver.com/luexr and my personal ID is 17AZX32.
