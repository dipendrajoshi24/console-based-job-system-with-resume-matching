## Console-Based Job System with Resume Matching  
A simple yet functional **console project built in C**, designed to simulate how a real-world job portal (like LinkedIn or Naukri) might work — but entirely text-based.  
This project was built as part of my **BCA journey**, focusing on file handling, modular programming, and basic keyword-based resume matching.

##  Features  
1. User registration and login system  
2. Separate roles for users and admin  
3. Job posting and management  
4. Resume submission and keyword-based job matching  
5. Persistent data storage using`.txt` and `.csv` files  
6. Modular C code structure for clarity and scalability  


##  Project Idea  
I wanted to create something practical and realistic using **core C concepts** — something that handles users, files, and data like a small database.  
So this project became a mini **job portal system** that runs in the console.  
It helped me understand how **file systems** can act like databases and how **modules** make large codebases manageable.  

##  How to Run  
1. Clone this repository:  
   bash
   git clone https://github.com/dipendrajoshi24/console-based-job-system-with-resume-matching.git
Move into the project folder:

cd console-based-job-system-with-resume-matching
Compile the project (using the Makefile):

make
Run the executable:

./jobfinder
(On Windows: jobfinder.exe)


## Project Structure
1. main.c Entry point; controls main flow
2. user.c / user.h Handles registration, login, user validation
3. job.c /job.h Manages job creation,listing,and deletion
4. application.c / application.h Handles job applications and matching
5. data.c / data.h  File storage and data persistence
6. utils.c / utils.h Helper and string processing functions.
7.users.txt Stores user data
8. jobs.txt Stores job listings
9. applications.csv Stores job applications
10. Makefile Compiles all modules easily
11. README.md Project documentation

 
## Future Improvements
Enhance matching logic with weighted keywords

Add admin dashboard for better management

Switch from file storage → SQLite database

Add GUI (maybe with C++ or Python frontend)

Improve search and filtering

#Author
Dipendra Joshi

## License
Licensed under the MIT License — free to use, modify, and share.







