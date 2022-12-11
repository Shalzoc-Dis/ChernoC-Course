// Things that still need investigation
// trailing return types


// A Preprocessor statement is anything with a '#'
// #include finds a file and pastes it into this file
#include <iostream>     // Angular brackets tell the compiler to search include path folders    Quotes could be used for all of them
#include "Log.h"        // Find files relative to the current file
#include <array>        // So we can use C++ arrays
#include <string>       // So we can use C++ strings
#include <stdlib.h>     // Standard C library
#include <memory>       // Smart pointers
#include <vector>       // For dynamic arrays
#include <array>        // For C++ arrays
#include <functional>   // For Tuple classe
#include <utility>      // So we can make the tuple

#include <GLFW/glfw3.h> // This is a library I have included
//  extern "C" glfwInit();  // This is like the #include above, but this only takes the glfwInit() function
// Files without a file extention like iostream are C++ standard libraries. Standard libraries with a file extention are C standard libraries


#define WAIT std::cin.get() // defines WAIT to be evaluated to std::cin.get()
// If we are in debug mode, LOG will print something. If we are not, it will not
#ifdef PG_DEBUG
#define LOG(x) std::cout << x << std::endl
#else /*defined(PR_RELEASE)*/
#define LOG(x)
#endif
// Backslash allows for multi-line defines
#define MAIN int main() \
{\
    std::cout << "Hello World" << std::endl;\
}

using std::cout;
using std::endl;
using string = std::string; // Now we only need to type "string" instead of "std::string" everywhere
//using shorthand = custom_datatype;    // This can be very useful too

// Inline means that the compiler simply replaces the function call with it's body
// Static outside of a class means that the symbol definition is internal, so only declaired for this translation unit, file in this case
// Static inside of a class or struct means that variable will share memory with all instances of the class.

static int s_StaticVariable = 5;    // s_ naming convention for static
// If I defined s_StaticVariable again in another file, but as a global instead of a static, other files will use the global verison. Only this translation unit will use the static version
// extern int e_ExternVariable; will tell the linker to look for a definition of this in another translation unit. Would not work if e_ExternVariable is defined as static
// static is like the private: keyword in a class. It is best to use static if possible

struct Entity
{
    int x, y;
    static int staticX, staticY;

    void print()
    {
        cout << x << " | " << y << endl;
    }
};

int Entity::staticX;    // Because these are static, they must be defined so the linker can link to them
int Entity::staticY;

int Multiply(int a, int b)
{
    return a * b;
}

void Increment(int& var)    // Passing a reference to our variable to avoid an unnecessacy copy of the variable
{
    var++;
}

void IncrementWithPtr(int* var) // Passing in a pointer to our variable
{
    (*var)++;   //  Because of order of operations, it would have incrememted the address first, and then dereferenced the pointer. This is not what we want, so we add these perenthesis
}

class Car
{
    // Public, private, protected are visibility modifiers
    // Structs are set to public by default and classes are set to private by default
    // Public means that everything can access this data from anywhere
    // Protected means that this entity class and all derived classes can access the data
    // Private means that only this entity class can access these things. This means no derived classes or functions outside of this class can access this data. The only exception is a "friend" class
    
public:

    // One class could have several constructors, which one is used depends on what parameters you passed in to it
    // Car() = delete; If I did not want instances of Car to be able to be made, only the class methods to be used. The default constructor can be deleted

    std::string carName;
    // Comments right above a class method show up in the intelliSense when said functions are being called
    Car(const std::string& name)
    {
        carName = name;
    }
                // Depending on what parameters you pass, the computer will select the appropriate constructor
    Car()
    {
        cout << "Created Entity: Car" << endl;
    }
    ~Car()  // The destructor is called when the class instance goes out of scope if it was declared on the stack
    {
        cout << "Destroyed Entity: Car" << endl;
    }

    // This is for organisation and better performance when using class types, because it avoids the default constructor creating an empty object and immediatly throwing it away once it is overridden by the newly initialised one
    /*  Constructor with member initialiser list. The variables need to be listed in order they are declaired in otherwise that can cause errors
    Car()
        : price(0), carName("Unspecified")
        {
        }
    */


    const char* name;   // Variables in a class are called members. Convention is to write them like this: m_Name
    unsigned int price;
    int x = 0;
    int y = 0;
    int speed = 0;


    void move(int xa, int ya)   // A function inside a class is called a class method
    {
        x += xa * speed;
        y += ya * speed;
    }
};

class Mercedes : public Car // Mercedes is a new class inheriting from Car. Mercedes now contains all data and methods Car has
{
public:
    char type;

    void printName(const char* name)
    {
        cout << name << endl;
    }
};

// Virtual functions and polymorphism
// BaseClass* baseClassObject = new BaseClass(); 
// InheritingClass* inheritingObject = new InheritingClass("Cherno");
// cout << baseClassObject->GetName() << endl;    // Prints "BaseClass"
// cout << inheritingObject->GetName() << endl;    // Prints "Cherno"

// However, if we create the InheritingClass object to a BaseClass pointer like this:
// BaseClass* newBase = inheritingObject;
// cout << newBase->GetName(); // Prints "BaseClass" eventough I am refering to an inheritingClass object. 

// This is an interface
class Printable // BaseClass and thus also InheritingClass inherit from Printable
{
public:
    virtual std::string GetClassName() = 0; // This is a pure virtual function
};

class BaseClass : public Printable
{
public:
    virtual std::string GetName()   // The above problem can be fixed by making this a virtual method
    { 
        return "BaseClass"; 
    }
    // Pure virtual function (Interface or abstract Method)
    // Allows us to define a method in a base class withoug an implementation and force derived classes to create the definition
    virtual std::string PureVirtualMethodExample() = 0;   // The '= 0;' makes it a pure virtual function

    std::string GetClassName() override { return "BaseClass"; }
};
class InheritingClass : public BaseClass    // you can add a comma and any other classes it shoud inherit from
{
private:
    std::string m_Name;
public:
    InheritingClass(const std::string& name)
    {
        m_Name = name;
    }

    std::string GetName() override  // Because this is a virtual method being overridden, we need to make it an override
    {
        return m_Name; 
    }

    std::string GetClassName() override { return "InheritingClass"; }
};

void PrintThing(Printable* obj)
{
    cout << obj->GetClassName() << endl;
}

// Enum class | what integer type we want it to be. It has to be an integer, a float would not work
enum Example :  unsigned char
{
    // By default, the first value will be 0, the second will be 1 greater, the third will be 1 greater than the second one, ect.
    A, B, C
    // You can also specify what these values should be
};


class ImplicitConversion
{
private:
    string m_Name;
    int m_Age;
public:
    // Can be called implicitly
    ImplicitConversion(const string& name)
        : m_Name(name), m_Age(-1) {}
    // Cannot be called implicitly
    explicit ImplicitConversion(int age)
        : m_Name("Undefined"), m_Age(age) {}

};

void PrintImplicitConversion(const ImplicitConversion& e)
{
    // Some stuff
}

struct Vector2
{
    float x, y;

    Vector2(float x, float y)
        : x(x), y(y) {}

    // Add function to avoid operator overloading
    Vector2 Add(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }
    // Add function with operator overloads
    Vector2 operator+(const Vector2& other) const
    {
        //return Vector2(x + other.x, y + other.y);
        return Add(other);
    }


    Vector2 Multiply(const Vector2& other) const
    {
        return Vector2(x * other.x, y * other.y);
    }
    Vector2 operator*(const Vector2& other) const
    {
        //return Vector2(x * other.x, y * other.y);
        return Multiply(other);
    }

    bool operator==(const Vector2& other) const
    {
        return other.x == x && other.y == y;
    }

    bool operator!=(const Vector2& other) const
    {
        return other.x != x || other.y != y;
    }
};
// Overloading the bitwise shift left operator
std::ostream& operator<<(std::ostream& stream, const Vector2& other)
{
    stream << "(" << other.x << " | " << other.y << ")";
    return stream;
}

class ThisKeywordExample
{
public:
    int x, y;

    ThisKeywordExample(int x, int y)
    {
        // We cannot just say x = x; because this will not assign the parameter x to the member variable x
        // Instead, we need to use the "this" keyword which is just a pointer to the current instance of the object containing the method
        this->x = x;
        (*this).y = y;  // The arrow operator automatically dereferences the pointer
    }
};

// This is a basic scoped pointer class
class ScopedPtr
{
private:
    Car* m_Ptr;
public:
    ScopedPtr(Car* ptr)
        : m_Ptr(ptr)
    {

    }

    ~ScopedPtr()
    {
        delete m_Ptr;
    }
};

// Copying and Copy constructors
class StringClass
{
    // This is an "old-school" way of doing it
private:
    char* m_Buffer;
    unsigned int m_Size;
public:
    StringClass(const char* string)
    {
        m_Size = strlen(string);
        m_Buffer = new char[m_Size + 1];
        memcpy(m_Buffer, string, m_Size);   // This copies our memory from string in to m_Buffer
        m_Buffer[m_Size] = 0;   // Adding our own NULL termination character
    }

    // Our copy constructor. A copy constructor takes a reference to a variable with the same type
    // A copy cnstructor that only initialises member variables is the default one C++ supplies us with.
    // If we don't want to allow copying, we can make the copy constructor equal to delete;
    StringClass(const StringClass& other)
        :m_Size(other.m_Size)   // Because this is just an int, we can shallow copy it
    {
        m_Buffer = new char[m_Size + 1];    // Creating a deep copy of m_Buffer, so copying the memory contents instead of the memory address
        memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
    }

    ~StringClass()
    {
        delete[] m_Buffer;  // To prevent memory leaks
    }

    // Friends can access private members
    friend std::ostream& operator<<(std::ostream& stream, const StringClass& string);
};
// Overloading an operator to allow us to print our string to the console
std::ostream& operator<<(std::ostream& stream, const StringClass& string)
{
    stream << string.m_Buffer;  // We can access m_Buffer because this function is a friend of our String class
    return stream;
}

// Example classes and operators for std::vector
struct Vertex
{
    float x, y, z;

    Vertex(int x, int y, int z)
        :x(x), y(y), z(z) {}
};
std::ostream& operator<<(std::ostream& stream, const Vertex& vertex)
{
    stream << "(" << vertex.x << " | " << vertex.y << " | " << vertex.z << ")";
    return stream;
}

template<typename T>    // typename is a template parameter. (typename and class are synonyms)
void TemplatePrint(T input) { cout << input << endl; }  // This function is not one that "exists". Once the programme is being compiled and this function called, it gets created with the type it needs.

template<typename R, int N> // Could also do: template<typename T, int N> as it takes multiple parameters
class TemplateArrayClass
{
private:
    R m_Array[N];
public:
    int getSize() const { return N; }
};

int main() // Application starts here. It is the entry point. Things can be returned from main and the output will say "Exited with code X"
{
    // When in debug mode and debugging, uninitialised variables will be set to 0xcccccccc. This can be useful for knowing if the variable has been initialised or not
    // Every two digits in the memory view are equal to one byte
    // Local and auto while debugging will show you what Visual Studio thinks is relevant, but watch will let you enter what you want to see
    // If the value in the debug view is red, that means that is changed since the last breakpoint
    // The line the yellow arrow is on is the next line it will execute - it has not been executed yet
    // While debugging, you can set new breakpoints and then continue to where they are to skip around faster


    // Loops
    // Init i \ Run loop while true \ Code that will be called before the next itteration
    for (int i = 0; i < 5; i++)
    {
        cout << i << endl;
        // continue; -> go to the next iteration of this loop if there is one, otherwise end the loop
        // break; -> end the loop
        // return; -> exit the entire function
    }

    // Pointers
    // Cretaing data on the stack
    int var = 8;        // Create a variable with value 8
    int* ptr = &var;    // Create a pointer with the adress of var
    *ptr = 10;          // Write 10 to the adress ptr is holding, changing the value of var

    // Creating data on the heap
    char* buffer = new char[8];     // A char is one byte of memory. This asks the computer to create space for eight bytes of memory
    memset(buffer, 0, sizeof(char) * 8);       // memset() takes a pointer to the beginning of our data, the value it is supposed to fill it with, and the size of the chunk in bytes

    // A pointer to a pointer
    char** charPtr = &buffer;

    delete[] buffer;    // Deleting buffer because we allocated it on the heap

    // References (basically pointers)
    int a = 5;
    int& ref = a;       // Creating a reference pointer to a. A reference must always be initialised
    // int* ref = &a;   // This is very simmilar
    ref = 2;        // Is exactly like a = 2; For all intents and purposes, ref is a. It is not a seperate variable
    // ref references a. This cannot be changed, it will always reference a. ref = otherVar will only set a to the value of otherVar
    IncrementWithPtr(&a);   // This one uses a pointer, they are more powerful but not as clean as a reference
    Increment(a);           // This one using the reference is much cleaner. If you can get away with a reference, use it


    // Classes
    Car myCar;  // myCar is an object, or an instance of a class
    myCar.name = "John";
    myCar.price = 65000;
    myCar.move(1, -1);

    // Inheritance
    // Mercedes inherits from Car
    Mercedes myMercedes;
    myMercedes.move(1, 2);  // There is no move() in Mercedes, but there is one in Car




    // Structs
    // Technically, the only difference between a struct and a class is that everything in a struct is set to public by default, while everything in a class is private by default
    // Creating two entities and initialising their non-static members
    Entity e;
    e.x = 2;
    e.y = 3;
    Entity e1 = { 5, 8 };   // This is a struct initialiser
    e.print();
    e1.print();
    // Initialising their static members
    e.staticX = 2;
    e.staticY = 3;
    e1.staticX = 5;
    e1.staticY = 8;
    e.print();
    e1.print(); // These two print commands will return the same result, because there is only one staticX and one staticY all instances of Entity share
    // Because these are shared values, we may as well refer to them like this:
    Entity::staticX = 5;    // Kind of like a namespace
    Entity::staticY = 8;
    // Static methods cannot access non-static variables. The method would not know which entity's variables to access


    // Log class
    Log log;
    log.setLevel(Log::LevelInfo);
    log.warn("Log warn test");


    // Enums (Enumerations)
    // An enum is a way to name a value. It helps us define a set of values. It is useful if you want to use ints to represent things, but you want to give the values a name
    Example value = B;
    // Example value = 5; would give an error


    // Arrays
    // Creating an array stack
    int exampleArray[5];
    for (int i = 0; i < 5; i++)
    {
        exampleArray[i] = i;
    }

    cout << exampleArray[0] << endl;    // Prints the first element of the array
    cout << exampleArray << endl;       // Prints the address of the array

    exampleArray[2] = 5;    // These are identical statements
    *(exampleArray + 2) = 5;

    // To find the length of a stack allocated array you can do this:
    // This does not work with heap allocated arrays because the sizeof() function would return the size of the pointer to the first element
    int count = sizeof(exampleArray) / sizeof(int); // The int here is the data type of the array

    // Creating an array on the heap
    int* heapExampleArray = new int[5];
    // You must delete it after you are done with it
    delete[] heapExampleArray;

    // Standard array (only C++11 and higher)
    std::array<int, 5> standardArray;   // Creates a standard array of type int with length 5
    cout << "standardArray has " << standardArray.size() << " elements." << endl;


    // Strings
    // In C++, double quotes create a const char*, while single quotes make a char
    const char* cString = "Cherno"; // This is a C-style string. These are allocated on the stack, so they don't need to be deleted
    // It must be const. If we wanted to be able to change our string, it would need to be char cString[] = "Cherno";
    // One of these strings has a null termination character at the end, so the program knows how long the string is
    char stringArray[7] = { 'C', 'h', 'e', 'r', 'n', 'o', 0 };  // Here we created an array for our string. The 0 at the and means NULL
    cout << stringArray << " is " << strlen(cString) << " characters long." << endl;    // Does not print the address of the first element, prints the array untill it hits NULL, so the null termination character

    // std::string;
    std::string cppString = "Cherno";
    cppString += " hello";  // Concatnates the two strings
    cout << cppString  << " is " << cppString.size() << " characters long." << endl;
    bool contains = cppString.find("no") != std::string::npos;  // If sppString contains no. std::string::npos represents an illegal position. string.find("X") returns the posiiton of X
    // If writing a function that takes in a string, make sure not to do this:
    // void PrintString(std::string name) { cout << name << endl; }
    // The above function would make a copy of the string and pass it in (So if you changed the string inside the function, the original would not be changed)
    // String copying and operation with them are generally slow, so a const reference is much better for a function:
    // void PrintString(const std::string& name) { cout << name << endl; }

    // String literals
    // A string literal is a series of characters inbetween some double quotes
    "Cherno";   // Could also be "Cherno\0" because \0 means NULL
    // There are other types of characters
    const char* name = "Cherno";        // 1 byte per character     >> no or "u8" prefix
    const wchar_t* name2 = L"Charno";   // 2 bytes per character    >> "L" prefix       A wchar_t can either be 2 or 4 bytes, depending on the compiler
    const char16_t* name3 = u"Charno";  // 2 bytes per character    >> "u" prefix
    const char32_t* name4 = U"Charno";  // 4 bytes per character    >> "U" prefix

    // std::string name = "Charno" + "hello"; would not work
    // Instead, you could do std::string name = std::string("Cherno") + "hello";
    // In C++14 they introduced a new feature:
    // using namespace std::string_literals;
    // std::string name = "Charno"s + "hello";  The s after "Cherno" is an operator that returns a standard string

    // You can also append an "R" to the beginning of a string to have it ignore escape characters
    // const char* example = R"(Line1
    // Line2
    // Line3
    // Line4)";
    // This just makes it easier to type in the editor if you want multiple lines of text (the perentheses are neccessary in this instance)

    // string raw;
    // cin.ignore();    // This will allow the user to enter multiple words seperated by spaces
    // std::getline(std::cin, raw);




    // Const 
    const int* constVal = new int;  // A const pointer will allow you to change the address the pointer is pointing to, but not the value at that address
    int const* constVal2 = new int; // This is the same as the line above
    int* const constPtr = new int;  // This is the opposite, the value at the pointer's held address can be changed, but the address the pointer holds cannot
    /*
    class Entity
    {
    private:
        int m_x, m_y;
        char* one, two;     // This will make one char pointer called "one" and make a normal char called "two"
        char* one0, *two0;  // This will make two char pointers

        mutable int var;    // mutable means that this variable can be modified by a const method
    public:
        int GetX() const    // This const says that this method will not be modifying any data. Only works for a class method
            {
                return m_x;
            }

        const int* const GetY() const   // Says that this method will return an int ptr the address it holds cannot be changed, the value at that address cannot be changed, and theis method won't change any data
            {                           // The exception is when you are trying to modify a mutable variable. They can be modified by a const method
                var = 2;
                return m_y;
            }
    };
    */

    
    delete constVal;
    delete constVal2;
    delete constPtr;



    // Ternary operator
    static int s_Level = 1;
    static int s_Speed = 2;

    // Normal if-statement
    if (s_Level > 5)
        s_Speed = 10;
    else
        s_Speed = 5;

    // Ternary operator
    s_Speed = s_Level > 5 ? 10 : 5;
    // Nested ternary operator. Not neccessarily the best solution
    s_Speed = s_Level > 5 ? s_Level > 10 ? 15 : 10 : 5;

    // Instantiating objects on the stack
    // You would want to instantiate objects on the stack when ever possible, because the memory is deallocated once it goes out of scope. There are no memory leaks
    // When a function gets called, a stack frame is created for it where all it's variables and objects are stored. Once it goes out of scope, the stack "pops" and is destroyed
    // A scope can be a loop, conditional, or empty scope (an empty scope is defined by two lone curley brackets)
    // The stack is also not very large, so if you have a large class or many of them, you need to allocate it on the heap
    Car newCar0;            // Uses default constructor
    Car newCar1("StackCar");     // Is exactly like: Car newCar1 = Car("Car");

    // Heap allocation
    Car* newCar2 = new Car("HeapCar");
    // You need to manually deallocate it again
    delete newCar2;

    // The new keyword
    int A = 2;
    int* heapB = new int;
    Car* carHeap = new Car[5];  // Creates an array of 5 cars. This also calls the constructor
    // The "new" operator calls the C function malloc(sizeInBytes) which stands for "memory allocate"
    // In general, malloc() is not something you should use in C++
    Car* carHeapMalloc = (Car*)malloc(sizeof(Car));   // This is like: Car* carHeapMalloc = new Car(); The only difference is that "new" also calls the class' constructor, malloc() does not
    // Of course, if you use new, you need to delete it again later
    delete heapB, carHeapMalloc;   // "delete" also calls the destructor of the function
    delete[] carHeap;


    // Implicit Conversion
    ImplicitConversion a("Example");    // ImplicitConversion a = "Example";    // These lines of code are the same
    ImplicitConversion b(34);           // ImplicitConversion b = 34;           // The compiler has chosen the correct constructor

    //PrintImplicitConversion(22);            // The compiler has preformed one implicit conversion from 22 to an ImplicitConversion object
    //PrintImplicitConversion("Cherno");    // This is not possible because the compiler would have to convert the const char* that is "Cherno" to a string which would then have to be converted to an ImplicitConversion object. It can only do one conversion.
    PrintImplicitConversion(string("Cherno"));  // This is fine because there is only one implicit conversion
    // Explicit disables the "implicit" keywordso the constructor must be called
    //PrintImplicitConversion(22);  // Does not work because this constructor is labled as "explicit"


    // Operators and overloading
    // Operators are symbols we use instead of functions including, but not limited to: mathematical operators like "+", pointer operators like "&" and "->", "new" and "delete" keywords
    // Overloading means to change the behaviour of, so operator overloading is when you change how an operator works in your programme
    
    Vector2 pos(4.0f, 4.0f);
    Vector2 speed(0.5f, 1.5f);
    Vector2 powerup(1.5f, 2.5f);

    Vector2 result0 = pos.Add(speed.Multiply(powerup));     // This does not use operator overloading
    Vector2 result1 = pos + speed * powerup;                // This uses operator overloading

    if (result0 == result1)
        cout << result1 << endl;    // The bitwise left operator also needs to be overloaded to allow for this
    if (result0 != result1)
        cout << "Results don't match!" << endl;




    // Scoped pointers
    ScopedPtr e = new Car();
    // Once ScopedPtr goes out of scope, it will delete the pointer to the heap allocated Car object. This will also detroy the Car object.

    // Smart pointers (require #include <memory>)
    // A unique pointer is a pointer that will be destroyed and delete will be called when it goes out of scope. Unique pointers cannot be copied
    {
        std::unique_ptr<Car> uniquePtrCar = std::make_unique<Car>();    // Creating a unique pointer for a car object
        uniquePtrCar->move(1, 0);
        // Once this scope ends, our uniquePtrCar object will be destroyed even though it was created on the heap
    }

    // A shared pointer is a pointer that uses a reference counter that only deletes the object once all pointers to that object go out of scope
    {
        std::shared_ptr<Car> sharedPtrCar0 = std::make_shared<Car>();
        {
            std::shared_ptr<Car> sharedPtrCar1 = sharedPtrCar0; // Shared pointers can be copied
        }   // sharedPtrCar1 is destroyed here, but sharedPtrCar0 lives on
    }       // sharedPtrCar0 is finally destroyed and the object sharedPtrCar0 and sharedPtrCar1 were pointing to is destroyed

    // A weak pointer can hold a copy of a shared pointer without increasing the reference counter
    // This means a weak pointer can store an address to an object without keeping it alive like a shared pointer does
    // This is useful for when you have a list of object you don't care about keeping alive, but want a way ask if they are. You simply make a weak pointer and ask if it is NULL at some point


    // Copying
    StringClass stringClass0 = "Cherno";
    // If we hadn't defined our own copy constructor this would have caused a crash because...
    StringClass stringClass1 = stringClass0;  // This copies all the member vairables from stringClass0 to stringClass 1. This incudes the char* m_Buffer. 
    // This results in two class instances having the same pointer to a memory address. Once the buffer is deleted in the destructor of stringClass0, it is freed.
    // Then stringClass1 is destroyed and the destructor called again. This calls delete[] on memory we have already freed; this is not possible to do without a crash.

    // To prevent this, we need to make a deep copy. A deep copy copies the entire object instead of only the member variables
    // This is done with a copy constructor



    // std::vector
    std::vector<Vertex> vertices;
    vertices.reserve(3);    // This tells the vector to allocate space for three objects. This is an optimisation for when we know how many objects we will want to push in
    // This can be done in one line: std::vector<int> ints(3);  // Reserving space for 3 values
    vertices.push_back(Vertex(1, 2, 3));    // Adding things to the vector
    vertices.push_back(Vertex(4, 5, 6));    // Because there is no constructor for Vertex, we are using an initialiser list
    vertices.emplace_back(7, 8, 9);         // This is an optimisaiton that, instead of contructing an object and copying it into the array, constructs the object right where it needs to end up

    // Iterating over the entire vector array
    for (int i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i] << endl;
    }

    // Range based loop
    for (Vertex& v : vertices)  // There is a vertex reference, because it would copy everything otherwise
    {
        cout << v << endl;
    }

    vertices.erase(vertices.begin() + 1);   // Erases the second element
    vertices.clear();                       // Clears the entire array



    // Libraries with static linking
    // Static linking occurs at compile time which means that more optimisation can occur than with dynamic linking
    // Download the precompiled binaries and past them into a dependencies folder in the Solution Directory
    // Under project properties in C/C++ General, add additional include directories. Make sure the platform and build configuration are correct
    // Under Linker Input put the file you want to use so it can be linked correctly. In this case I add glfw3.lib
    // Under Linker General add the additional solution directories like the include directories, just the other files

    int glfwInitResult = glfwInit();    // Uses a function from the GLFW library. This is allowed because I #include <GLFW/glfw3.h>
    cout << glfwInitResult << endl;

    // Dynamic linking
    // Linking occurs at runtime
    // Add the dll.lib file in the linker input settings, instead of the .lib we would use if we were linking statically
    // The programme will also need the .dll file, so we paste it in with the .exe of the programme so the path is the same.


    // If we have multiple projects with one of them being a library (like an engine library and a game.exe) and we are using Visual Studio, we can right click on the project that will include the other one, and add it as a reference
    // If we were to modify the reference and try to build the .exe Visual Studio would also compile and build the references to make sure it works. Nice automation



    // Returning several variables 
    // 1: You could return a struct containing your values
    // 2: Pass the values in as references and change them in the function. Performance wise, this is a good solution
    // 3: Do the same thing with the reference with a pointer. This allows for us to pass in nullptr if we don't want that return. (Make sure to check if the pointer is valid before writing to it in this case)
    // 4: Return an array if all return values have the same type. std::array can be very good for this
    // 5: Same as above, only using a vector. The difference is that a vector uses heap memory and an array uses stack memory
    // 6: Tuple, a class that can contain any amount of variables without regard for the type (a pair is the same thing, only that there can only be two. To get values from that you can use source.first and source.second)
    //      std::tuple<int, char> TupleFunction(int inInt, char inChar) { return std::make_pair(inInt, inChar); }
    //      std::tuple<int, char> tupleReturn = TupleFunction(2, 'A');  // Could also use: auto tupleReturn = TupleFunction(2, 'A');
    //      int outInt = std::get<0>(tupleReturn);
    //      char outChar = std::get<1>(tupleReturn);



    // Templates
    // A template is essentially the compiler following a set of rules and writing code for you
    // A way to use templates is to write a function that is always the same, only taking different types
    // A template function doesn't exist until it is called, so one containing some error that is never called will not result in a failed compilation
    // Example definition before main()
    TemplatePrint(5);
    TemplatePrint<float>(5.5f); // The type can also be specified using angular brackets
    // Template example
    TemplateArrayClass<int, 5> templateArray;   // Creates an array of five ints



    // Stack and Heap memory
    // The stack is a pre-defined size, normally 2 MB
    // The heap is also pre-defined, but it can grow depending on our application's needs
    // The stack has a pointer of the last bit of occupied memory, which moves when we allocate on the stack. Allocating on the stack is very fast. Once the memory goes out of scope, it is cleared
    // The heap stores things at very different locations, so it is slower finding things in it. There is a lot of "bookkeeping" that needs to happen, so dynamic allocation is very expensive



    // Macros
    // Macros as preprocessor statements are basically a find and replace feature that happens before the compilation
    //std::cin.get(); // Should pause execution of the programme until enter is pressed.
    WAIT;   // This is not a great example

    // They can also take parameters
    LOG("Hello");

    // Macros can be useful for things like logging systems you want to have running in Debug mode, but not Release mode
    // To use them like this, you need to go to project settings and under the configuration you want (not All Confugurations) add a DEBUG preprocessor definition

    // We can also disable blocks of code like this:
#if 0
    This is now disabled
#endif
        LOG("Very nice");


    // The auto keyword
    // It is basically a type specifier without a set type. C++ will work out what type autoB must become in otder to make it take the value of autoA
    int autoA = 5;
    auto autoB = a;



    // std::array


    std::cin.get(); // Waits for you to press enter
    while (true);   // Keeps the programme from closing 
}