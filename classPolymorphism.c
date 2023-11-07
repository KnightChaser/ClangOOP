#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  EMPLOYEE   1
#define  DOCTOR     2

typedef struct Person Person;

typedef struct {
    char name[100];
    char position[100];
    char email[100];
} EmployeeData;

typedef struct {
    char name[100];
    char specialization[100];
    char email[100];
} DoctorData;

// Diverge the selection of the Person type
typedef union {
    EmployeeData employee;
    DoctorData doctor;
} PersonData;

// Person
typedef struct Person {
    PersonData data;
    
    void (*selfIntroduce)(const Person *this);
    void (*updatePersonalInformation)(Person *this, 
                                      const char *updatedName, 
                                      const char *updatedPosition, 
                                      const char *updatedEmail);
} Person;

Person *newPerson(const char *registeredName, 
                  const char *registeredPosition, 
                  const char *registeredEmail, 
                  int personType);                              // constructor
void deletePerson(Person *personPtr);                           // destructor
void selfIntroduce(const Person *this);                         // member function 1
void updatePersonalInformation(Person *this,                    // member function 2
                               const char *updatedName, 
                               const char *updatedPosition, 
                               const char *updatedEmail);

Person *newPerson(const char *registeredName, const char *registeredPosition, const char *registeredEmail, int personType) {
    
    Person *internalPersonObject = (Person *)malloc(sizeof(Person));

    if (internalPersonObject != NULL) {
        if (personType == EMPLOYEE) {
            strncpy(internalPersonObject->data.employee.name, registeredName, 
                    sizeof(internalPersonObject->data.employee.name));
            strncpy(internalPersonObject->data.employee.position, registeredPosition, 
                    sizeof(internalPersonObject->data.employee.position));
            strncpy(internalPersonObject->data.employee.email, registeredEmail, 
                    sizeof(internalPersonObject->data.employee.email));
                    
        } else if (personType == DOCTOR) {
            strncpy(internalPersonObject->data.doctor.name, registeredName, 
                    sizeof(internalPersonObject->data.doctor.name));
            strncpy(internalPersonObject->data.doctor.specialization, registeredPosition, 
                    sizeof(internalPersonObject->data.doctor.specialization));
            strncpy(internalPersonObject->data.doctor.email, registeredEmail, 
                    sizeof(internalPersonObject->data.doctor.email));
        }
        
        // must executed
        internalPersonObject->selfIntroduce = selfIntroduce;
        internalPersonObject->updatePersonalInformation = updatePersonalInformation;
    }
    else {
        printf("Memory allocation failed during allocating internalPersonObject in Person *newPerson().\n");
        return NULL;
    }
    
    return internalPersonObject;
}

void deletePerson(Person *personPtr) {
    free(personPtr);
}

void selfIntroduce(const Person *this) {
    if (this->selfIntroduce != NULL) {
        if (this->selfIntroduce == selfIntroduce) {
            printf("Hello! My name is %s whose job is %s. You can contact me to %s.\n",
                this->data.employee.name, this->data.employee.position, this->data.employee.email);
        } else {
            printf("Hello! My name is %s, a doctor specializing in %s. You can contact me at %s.\n",
                this->data.doctor.name, this->data.doctor.specialization, this->data.doctor.email);
        }
    }
}

void updatePersonalInformation(Person *this, const char *updatedName, const char *updatedPosition, const char *updatedEmail) {
    if (this->selfIntroduce == selfIntroduce) {
        if (updatedName != NULL)
            strncpy(this->data.employee.name, updatedName, sizeof(this->data.employee.name));
        if (updatedPosition != NULL)
            strncpy(this->data.employee.position, updatedPosition, sizeof(this->data.employee.position));
        if (updatedEmail != NULL)
            strncpy(this->data.employee.email, updatedEmail, sizeof(this->data.employee.email));
    } else {
        if (updatedName != NULL)
            strncpy(this->data.doctor.name, updatedName, sizeof(this->data.doctor.name));
        if (updatedPosition != NULL)
            strncpy(this->data.doctor.specialization, updatedPosition, sizeof(this->data.doctor.specialization));
        if (updatedEmail != NULL)
            strncpy(this->data.doctor.email, updatedEmail, sizeof(this->data.doctor.email));
    }
}

int main(void) {
    
    // Create instances
    Person *personA = newPerson("Lee Garam", "hacker", "knightchaser@hacker.one", EMPLOYEE);
    Person *personB = newPerson("Dr. Klojure", "Cardiologist", "drKlojure@cardio.artoriahospital.com", DOCTOR);
    
    // Update instances    
    personA->selfIntroduce(personA);
    personA->updatePersonalInformation(personA, NULL, "Pro hacker", "knightchaser@hackclub.gachon.ac.kr");
    personA->selfIntroduce(personA);
    deletePerson(personA);

    personB->selfIntroduce(personB);
    personB->updatePersonalInformation(personB, NULL, "Orthopedist", "drKlojure@orthop.artoriahospital.com");
    personB->selfIntroduce(personB);
    deletePerson(personB);

    return 0;
}

// [Result]
// Hello! My name is Lee Garam whose job is hacker. You can contact me to knightchaser@hacker.one.
// Hello! My name is Lee Garam whose job is Pro hacker. You can contact me to knightchaser@hackclub.gachon.ac.kr.
// Hello! My name is Dr. Klojure whose job is Cardiologist. You can contact me to drKlojure@cardio.artoriahospital.com.
// Hello! My name is Dr. Klojure whose job is Orthopedist. You can contact me to drKlojure@orthop.artoriahospital.com.
