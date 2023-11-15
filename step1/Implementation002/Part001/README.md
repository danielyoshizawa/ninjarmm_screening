# Step 1 - Implementation 2
## Part 001 - Jobs

### Description

  For the 4 functionalities I decided to implement a simple clock in and out system,
  this will allow to cover hierarchy, containers, design patterns, memory mannagement, and
  other fancy stuff.

  This may not be a good representantion of the jobs resposibilities, however it can
  showcase some development principles.

  The approach to this implementation is TDD, build using Catch2 v3.3.2.
  
  Do not worry about libraries or any kind of configuration besides
  the basic c++ bread and butter, CMake and Gcc (or your favorite compiler).
  
  In the CMakeLists.txt are the specifications to proper fetch and install
  the testing library, and you can run the build_and_run.sh script to perform the build,
  run the test suit and the program.

  ```
  ./build_and_run.sh
  ```

  Worry not young warrior!
  
  If you prefer to run it manually, you can do it by runnig the following commands (Unix):
  ``` 
  mkdir build
  cd build
  cmake ..
  make -j
  make test
  ./<project_name>
  ```

  or
  
  ```
  mkdir build && cd build && cmake .. && make -j && make test && ./<project_name>
  ```

### Elements specifications
#### Model
##### Job

Job have 4 functionalities
1. clock in and out
    - Clock in and out should receive a date and time each, this will be 2 different functions
2. schedule vacation
    - Schedule Vacation should receive two dates (start and end inclusive)
3. call a sick day
    - Call a sick day should receive a date
4. report status
    - report status should print out a report with 
    - total worked time
    - Sick days
    - Extra hours
    - Missing hours
    - Planned Vacations
      
##### Developer

Developer should log their hours using the ClockSystem, and the rules are as follow:
- They need to work 8h per day
- Can have 9 sick days per year
- 30 days vacations
- Work only on weekdays
- Report should have a resume of activity

##### Pilots

Pilots should log their hours using the ClockSystem, and the rules are as follow:
- They can only clock in and out once a day
- They need to take at least 48 hours between flights (clock out )
- Unlimited sick days
- 30 days vacations
- Don't have a working schedule (can work on weekends)
- Report should have flight schedule based on clock in and out
  
##### ClockSystem
This component will represent an external service consumed by out application,
the logic will be kept in our application and this service will be responsible
for registering the hours, vacations and sick days.

#### Controller
The controller is the link between the view and the model, this will help with the
Separation of Concerns (SoC) of our application, it is a good practice in case we want
to change our view without affecting our model, for example.

Science!!! \<insert mindblowing meme\>

#### View
A simple console menu working inside a loop to perform the operations,
we don't need to go fancy here, since this is not part of the test.

We need a way to navigate between menus, feedback on the operations, and
an exit point.

The menus should be:
- Developer
    - Clock In
        - Date (yyyy-mm-dd)
        - Time (hh:mm)
    - Clock Out
        - Date (yyyy-mm-dd)
        - Time (hh:mm)
    - Sick Day
        - Date (yyyy-mm-dd)
    - Vacations
        - Initial Date (yyyy-mm-dd)
        - End Date (yyyy-mm-dd)
    - Report
    - Return
- Pilot
    - Same as for Developer
- Exit
