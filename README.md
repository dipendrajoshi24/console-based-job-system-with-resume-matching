#  Console-Based Job System with Resume Matching  

A simple yet functional **console project built in C**, designed to simulate how a real-world job portal (like LinkedIn or Naukri) might work — but entirely text-based.  
This project was built as part of my **BCA journey**, focusing on file handling, modular programming, and basic keyword-based resume matching.

##  Features  

✅ User registration and login system  
✅ Separate roles for users and admin  
✅ Job posting and management  
✅ Resume submission and keyword-based job matching  
✅ Persistent data storage using`.txt` and `.csv` files  
✅ Modular C code structure for clarity and scalability  


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


## 🗂️ Project Structure

│
├── main.c # Entry point; controls main flow
├── user.c / user.h # Handles registration, login, user validation
├── job.c / job.h # Manages job creation, listing, and deletion
├── application.c / application.h # Handles job applications and matching
├── data.c / data.h # File storage and data persistence
├── utils.c / utils.h # Helper and string processing functions
│
├── users.txt # Stores user data
├── jobs.txt # Stores job listings
├── applications.csv # Stores job applications
│
├── Makefile # Compiles all modules easily
└── README.md # Project documentation
 Future Improvements
Enhance matching logic with weighted keywords

Add admin dashboard for better management

Switch from file storage → SQLite database

Add GUI (maybe with C++ or Python frontend)

Improve search and filtering

 Author
Dipendra Joshi


License
Licensed under the MIT License — free to use, modify, and share.







