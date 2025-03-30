#include "ESP32Wiimote.h"                                                                         // Include the ESP32Wiimote library for Wiimote functionality.
#include "ESP32Servo.h"                                                                           // Include the library for the servo.

ESP32Wiimote wiimote;                                                                             // Create an instance of the ESP32Wiimote class.
Servo myServo;

int servoPin = 18;

int passwordSequence[] = {BUTTON_A, BUTTON_ONE, BUTTON_TWO, BUTTON_B};                             // Password sequence (A -> 1 -> 2 -> B)
int currentStep = 0;                                                                               // To keep track of the current step in the password sequence

void setup()
{
    Serial.begin(115200);                                                                           // Initialize the serial communication at 115200 baud rate.
    Serial.println("ESP32Wiimote Initialized");                                                     // Print a message indicating the start of the program.

    wiimote.init();                                                                                 // Initialize the Wiimote object.
    wiimote.addFilter(ACTION_IGNORE, FILTER_ACCEL);                                                 // Always add the filter to ignore accelerometer data

    myServo.attach(servoPin);
    myServo.write(0);

    Serial.println("Started");                                                                      // Print a message indicating the setup is complete.
}

void loop()
{
    wiimote.task();                                                                             

    if (wiimote.available() > 0)                                                                    // Check if there is new data available from the Wiimote.
    {
        ButtonState button = wiimote.getButtonState();                                              // Get the current state of the buttons.

        char buttonA = (button & BUTTON_A) ? 'A' : '.';
        char buttonB = (button & BUTTON_B) ? 'B' : '.';
        char buttonC = (button & BUTTON_C) ? 'C' : '.';
        char buttonZ = (button & BUTTON_Z) ? 'Z' : '.';
        char buttonOne = (button & BUTTON_ONE) ? '1' : '.';
        char buttonTwo = (button & BUTTON_TWO) ? '2' : '.';
        char buttonMinus = (button & BUTTON_MINUS) ? '-' : '.';
        char buttonPlus = (button & BUTTON_PLUS) ? '+' : '.';
        char buttonHome = (button & BUTTON_HOME) ? 'Home' : '.';
        char buttonLeft = (button & BUTTON_LEFT) ? '>' : '.';
        char buttonRight = (button & BUTTON_RIGHT) ? '<' : '.';
        char buttonDown = (button & BUTTON_DOWN)  ? 'v' : '.';
        char buttonUp = (button & BUTTON_UP)     ? '^' : '.';
        char lockDoor = (button & BUTTON_A && button & BUTTON_B);                            //To lock the door press a and b at the same time

        Serial.println(buttonA);
        Serial.println(buttonB);
        Serial.println(buttonTwo);
        Serial.println(buttonOne);




                                                                                                    // If the button matches the expected button in the sequence
        if (button & passwordSequence[currentStep])                                                 // Correct button pressed for the current step
        {
            Serial.print("Correct button pressed: ");
            currentStep++;                                                                          // Move to the next step in the password sequence

            if (currentStep == 4)                                                                         // Password sequence is complete (A -> 1 -> 2 -> B)
            {
                Serial.println("Password sequence entered! Hello!");
                myServo.write(180);
                currentStep = 0;                                                                          // Reset sequence after completion
            }

            if (lockDoor) {
            myServo.write(0); }                                                                              //Door is lockes with the AB combo press
        }
        else if (button != passwordSequence[currentStep] && button != NO_BUTTON)                             // Incorrect button pressed
        {
            
            Serial.println("Incorrect button pressed! Sequence reset.");                                     // Reset the sequence if any other button is pressed
            currentStep = 0;                                                                                 // Reset the password sequence
        }
    }
}
