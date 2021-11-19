#include<stdio.h>
#include<conio.h>
#include<windows.h>
#pragma warning(disable : 4996)

#define NUMBER_240_IN_HEXADECIMAL 0xF0
#define NUMBER_15_IN_HEXADECIMAL 0x0F
#define NUMBER_OF_DAYS_IN_WEEK 7
#define LOWEST_VALUE_FOR_YEAR 1600
#define MAX_NUMBER_OF_MONTHS 12
#define MIN_NUMBER_OF_MONTHS 1

struct Date {
    int day;
    int month;
    int year;
};

struct Remainder {
    int day;
    int month;
    char note[50];
};

void setPositionToPrintResultOnScreen(int coordinateX, int coordinateY)
{
    COORD coordinatesXAndY = { 0, 0 };
    coordinatesXAndY.X = coordinateX; coordinatesXAndY.Y = coordinateY;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinatesXAndY);
}

void setTheForegroundColorForPrintingInConsole(int foregroundColor)
{
    WORD fontColor;
    HANDLE HandleStdToGetOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO structureOFConsoleInfo;
    //We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(HandleStdToGetOutput, &structureOFConsoleInfo))
    {
        //Mask out all but the background attribute, and add in the forgournd color
        fontColor = (structureOFConsoleInfo.wAttributes & NUMBER_240_IN_HEXADECIMAL) + (foregroundColor & NUMBER_15_IN_HEXADECIMAL);
        SetConsoleTextAttribute(HandleStdToGetOutput, fontColor);
    }
    return;
}

void ClearConsoleToColors(int foregroundColor, int backgroundColor)
{
    WORD fontColor = ((backgroundColor & NUMBER_15_IN_HEXADECIMAL) << 4) + (foregroundColor & NUMBER_15_IN_HEXADECIMAL);
    HANDLE HandleStdToGetOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD resetTheCursorToTopLeft = { 0, 0 };
    DWORD countOfCharsWhereWrittenButNotUsed;
    CONSOLE_SCREEN_BUFFER_INFO structureOfConsoleInfo;
    SetConsoleTextAttribute(HandleStdToGetOutput, fontColor);
    if (GetConsoleScreenBufferInfo(HandleStdToGetOutput, &structureOfConsoleInfo))
    {
        //This fills the buffer with a given character (in this case 32=space).
        FillConsoleOutputCharacter(
            HandleStdToGetOutput
            , (TCHAR)32
            , structureOfConsoleInfo.dwSize.X * structureOfConsoleInfo.dwSize.Y,resetTheCursorToTopLeft
            , &countOfCharsWhereWrittenButNotUsed);
        FillConsoleOutputAttribute(
            HandleStdToGetOutput
            , structureOfConsoleInfo.wAttributes
            , structureOfConsoleInfo.dwSize.X * structureOfConsoleInfo.dwSize.Y
            , resetTheCursorToTopLeft, &countOfCharsWhereWrittenButNotUsed);
        //This will set our cursor position for the next print statement.
        SetConsoleCursorPosition(HandleStdToGetOutput, resetTheCursorToTopLeft);
    }
    return;
}

void SetColorAndBackground(int foregroundColor, int backgroundColor)
{
    WORD fontColor = ((backgroundColor & NUMBER_15_IN_HEXADECIMAL) << 4) + (foregroundColor & NUMBER_15_IN_HEXADECIMAL);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fontColor);
    return;
}
 
int checkLeapYear(int year) { 
    if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
        return 1;
    return 0;
}

void increaseOnemonth(int* month, int* year) {
    ++* month;
    if (*month > MAX_NUMBER_OF_MONTHS) {
        ++* year;
        *month = *month - MAX_NUMBER_OF_MONTHS;
    }
}

void decreaseOneMonth(int* month, int* year) { 
    --* month;
    if (*month < 1) {
        --* year;
        if (*year < LOWEST_VALUE_FOR_YEAR) {
            printf("No record available");
            return;
        }
        *month = *month + MAX_NUMBER_OF_MONTHS;
    }
}

int getNumberOfDaysForMonth(int month, int year) { 
    if (month == 2 && checkLeapYear(year) == 1) 
        return(29);
    else
        return(28);
    //the months from 1 to 7 will be 30 day if it even number ,otherwise 31 except month 2
    if (month >= 1 && month <= 7 && month % 2 == 1)
        return(31);
    else
        return(30);
    //the months from 8 to 12 will be 31 day if it even number ,otherwise 30
    if (month >= 8 && month <= 12 && month % 2 == 1)
        return(30);
    else
        return(31);

   return(-1);
}

 const char* getNameOfDay(int day) { 
    switch (day) {
    case 0:return("Sunday");
    case 1:return("Monday");
    case 2:return("Tuesday");
    case 3:return("Wednesday");
    case 4:return("Thursday");
    case 5:return("Friday");
    case 6:return("Saturday");
    default:return("Error in getName() module.Invalid argument passed");
    }
}

int getDayNumber(int day, int month, int year) {
    int dayNumber = 0, temp1, temp2, copyOfYear = year;
    year -= LOWEST_VALUE_FOR_YEAR;
    while (year >= 100) {
        dayNumber += 5;
        year -= 100;
    }
    dayNumber %= NUMBER_OF_DAYS_IN_WEEK;
    temp1 = ((year - 1) / 4);
    temp2 = (year - 1) - temp1;
    temp1 = (temp1 * 2) + temp2;
    temp1 %= NUMBER_OF_DAYS_IN_WEEK;
    dayNumber += temp1;
    dayNumber %= NUMBER_OF_DAYS_IN_WEEK;
    temp2 = 0;
    for (temp1 = 1; temp1 < month; temp1++) {
        temp2 += getNumberOfDaysForMonth(temp1, copyOfYear);
    }
    temp2 += day;
    temp2 %= NUMBER_OF_DAYS_IN_WEEK;
    dayNumber += temp2;
    dayNumber %= NUMBER_OF_DAYS_IN_WEEK;
    if (copyOfYear > 2000)
        dayNumber += 1;
    dayNumber %= NUMBER_OF_DAYS_IN_WEEK;
    return dayNumber;
}

const char* getDay(int day, int month, int year) {
    int tempToGetDay;
    if (!(month >= MIN_NUMBER_OF_MONTHS && month <= MAX_NUMBER_OF_MONTHS)) {
        return("Invalid month value");
    }
    if (!(day >= MIN_NUMBER_OF_MONTHS && day <= getNumberOfDaysForMonth(month, year))) {
        return("Invalid date");
    }
    if (year >= LOWEST_VALUE_FOR_YEAR) {
        tempToGetDay = getDayNumber(day, month, year);
        tempToGetDay = tempToGetDay % NUMBER_OF_DAYS_IN_WEEK;
        return(getNameOfDay(tempToGetDay));
    }
    else {
        return("Please give year more than 1600");
    }
}

int checkNoteIfExist(int day, int month,Remainder reminder) {
    FILE* filePointer = fopen("note.dat", "rb");
    if (filePointer == NULL) {
        printf("Error in Opening the file");
    }
    while (fread(&reminder, sizeof(reminder), 1, filePointer) == 1) {
        if (reminder.day == day && reminder.month == month) {
            fclose(filePointer);
            return 1;
        }
    }
    fclose(filePointer);
    return 0;
}

const char* getNameOfMonth(int month) {
    switch (month) {
    case 1: return("January"); break;
    case 2: return("February"); break;
    case 3: return("March"); break;
    case 4: return("April"); break;
    case 5: return("May"); break;
    case 6: return("June"); break;
    case 7: return("July"); break;
    case 8: return("August"); break;
    case 9: return("September"); break;
    case 10: return("October"); break;
    case 11: return("November"); break;
    case 12: return("December"); break;
    }
}

void getStartingLocation(int dayNumber, int& coordX, int& startingLocationDayForCalender) {
    switch (dayNumber) {
    case 0:
        coordX = coordX;
        startingLocationDayForCalender = 1;
        break;
    case 1:
        coordX += 4;
        startingLocationDayForCalender = 2;
        break;
    case 2:
        coordX += 8;
        startingLocationDayForCalender = 3;
        break;
    case 3:
        coordX += 12;
        startingLocationDayForCalender = 4;
        break;
    case 4:
        coordX += 16;
        startingLocationDayForCalender = 5;
        break;
    case 5:
        coordX += 20;
        startingLocationDayForCalender = 6;
        break;
    case 6:
        coordX += 24;
        startingLocationDayForCalender = 7;
        break;
    default:
        printf("INVALID DATA FROM THE getOddNumber()MODULE");
        return;
    }
}

void printMonthWithDays(int month, int year, int coordX, int coordY, Remainder reminder) {
    int numberOfDays, dayNumber, startingLocationDayForCalender, day = 1, copyOfCoordX = coordX,copyOfCoordY = coordY;
    if (!(month >= MIN_NUMBER_OF_MONTHS && month <= MAX_NUMBER_OF_MONTHS)) {
        printf("INVALID MONTH");
        return;
    }
    if (!(year >= LOWEST_VALUE_FOR_YEAR)) {
        printf("INVALID YEAR");
        return;
    }
    setPositionToPrintResultOnScreen(20, coordY);
    printf("---------------------------\n");
    setPositionToPrintResultOnScreen(25, 6);
    printf(getNameOfMonth(month));
    printf(" , %d", year);
    setPositionToPrintResultOnScreen(20, 7);
    printf("---------------------------");

    coordY += 3;
    setPositionToPrintResultOnScreen(coordX, coordY);
    printf("S   M   T   W   T   F   S   ");
    coordY++;
    numberOfDays = getNumberOfDaysForMonth(month, year);
    dayNumber = getDayNumber(day, month, year);
    getStartingLocation(dayNumber, coordX, startingLocationDayForCalender);
    setPositionToPrintResultOnScreen(coordX, coordY);
    if (startingLocationDayForCalender == 1) {
        setTheForegroundColorForPrintingInConsole(12);
    }
    if (checkNoteIfExist(day, month, reminder) == 1) {
        SetColorAndBackground(15, 12);
    }
    printf("%02d", day);
    SetColorAndBackground(15, 1);
    for (day = 2; day <= numberOfDays; day++) {
        if (startingLocationDayForCalender % NUMBER_OF_DAYS_IN_WEEK == 0) {
            coordY++;
            startingLocationDayForCalender = 0;
            coordX = copyOfCoordX - 4;
        }
        coordX = coordX + 4;
        startingLocationDayForCalender++;
        setPositionToPrintResultOnScreen(coordX, coordY);
        if (startingLocationDayForCalender == 1) {
            setTheForegroundColorForPrintingInConsole(12);
        }
        else {
            setTheForegroundColorForPrintingInConsole(15);
        }
        if (checkNoteIfExist(day, month, reminder) == 1) {
            SetColorAndBackground(15, 12);
        }
        printf("%02d", day);
        SetColorAndBackground(15, 1);
    }
    setPositionToPrintResultOnScreen(8, coordY + 2);
    setTheForegroundColorForPrintingInConsole(14);
    printf("Press 'n'  to Next, Press 'p' to Previous and 'q' to Quit");
    setPositionToPrintResultOnScreen(8, coordY + 3);
    printf("Red Background indicates the NOTE, Press 's' to see note: ");
    setTheForegroundColorForPrintingInConsole(15);
}

void AddNote(Remainder reminder) {
    FILE* filePinter = fopen("note.dat", "ab+");
    system("cls");
    setPositionToPrintResultOnScreen(5, 7);
    printf("Enter the date(day/month): ");
    scanf_s("%d/%d", &reminder.day, &reminder.month);
    setPositionToPrintResultOnScreen(5, 8);
    printf("Enter the Note(50 character max): ");
    fflush(stdin);
    scanf(" %[^\n]", reminder.note);
    if (fwrite(&reminder, sizeof(reminder), 1, filePinter)) {
        setPositionToPrintResultOnScreen(5, 12);
        puts("Note is saved sucessfully");
        fclose(filePinter);
    }
    else {
        setPositionToPrintResultOnScreen(5, 12);
        setTheForegroundColorForPrintingInConsole(12);
        puts("\aFail to save!!\a");
        setTheForegroundColorForPrintingInConsole(15);
    }
    setPositionToPrintResultOnScreen(5, 15);
    printf("Press any key............");
    _getch();
    fclose(filePinter);
}

void showNote(int month,Remainder reminder) {
    int i = 0, isFoundTheMonth = 0;
    system("cls");
    FILE* filePointer = fopen("note.dat", "rb");
    if (filePointer == NULL) {
        printf("Error in opening the file");
    }
    while (fread(&reminder, sizeof(reminder), 1, filePointer) == 1) {
        if (reminder.month == month) {
            setPositionToPrintResultOnScreen(10, 5 + i);
            printf("Note %d Day = %d: %s", i + 1, reminder.day, reminder.note);
            isFoundTheMonth = 1;
            i++;
        }
    }
    if (isFoundTheMonth == 0) {
        setPositionToPrintResultOnScreen(10, 5);
        printf("This Month contains no note");
    }
    setPositionToPrintResultOnScreen(10, 7 + i);
    printf("Press any key to back.......");
    _getch();

}

void printOparationsMinu() {
    system("cls");
    printf("1. Find Out the Day\n");
    printf("2. Print all the day of month\n");
    printf("3. Add Note\n");
    printf("4. EXIT\n");
    printf("ENTER YOUR CHOICE : ");
}

int main() {
    struct Date dateFormat ;
    struct Remainder reminder ;
    reminder.note[0] = ' ';

    ClearConsoleToColors(15, 1);
    SetConsoleTitleA("Calender Project - Programming-technique.blogspot.com");

    int choice;
    char ch = 'a';
    while (1) {
        printOparationsMinu();
        scanf_s("%d", &choice);
        system("cls");
        switch (choice) {
        case 1:
            printf("Enter date (day/month/year) : ");
            scanf_s("%d/%d/%d", &dateFormat.day, &dateFormat.month, &dateFormat.year);
            printf("Day is : %s", getDay(dateFormat.day, dateFormat.month, dateFormat.year));
            printf("\nPress any key to continue......");
            _getch();
            break;
        case 2:
            printf("Enter month and year (month/year) : ");
            scanf_s("%d/%d", &dateFormat.month, &dateFormat.year);
            system("cls");
            while (ch != 'q') {
                printMonthWithDays(dateFormat.month, dateFormat.year, 20, 5, reminder);
                ch = _getch();
                if (ch == 'n') {
                    increaseOnemonth(&dateFormat.month, &dateFormat.year);
                    system("cls");
                    printMonthWithDays(dateFormat.month, dateFormat.year, 20, 5, reminder);
                }
                else if (ch == 'p') {
                    decreaseOneMonth(&dateFormat.month, &dateFormat.year);
                    system("cls");
                    printMonthWithDays(dateFormat.month, dateFormat.year, 20, 5, reminder);
                }
                else if (ch == 's') {
                    showNote(dateFormat.month,reminder);
                    system("cls");
                }
            }
            break;
        case 3:
            AddNote(reminder);
            break;
        case 4:
            exit(0);
        }
    }
    return 0;
}

