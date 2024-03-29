## Requirements:
1) Python **must be 3.10**
2) Microsoft Edge to view the QEP diagram
3) Postgres 
4) An existing postgres username, password and a database

## Python libraries:
1) Tkinter
2) JSON 
3) Selenium 
4) psycopg2

## Steps to run project
1) Ensure that there is the msedgedriver.exe in the zip file
2) Open the project in Pycharm 
3) Accept the creation of a new virtual interpreter as shown below
  * **Note: Ensure the base interpreter must be using 3.10 as shown in the image below.**
  * **Note: Please wait a moment for the installation process to complete before running the project.**

![image](https://user-images.githubusercontent.com/49061096/141414996-aab3ae6e-0c4e-4f24-9843-2faf45ba8ec9.png)


4) If Python libraries are not automatically installed after the creation of a virtual interpreter,
   #### Method 1: 
    * Open the requirements.txt to install the required Python libraries. 
      * A notification bar should be displayed like in the below image. Click on **install requirement.**
      * ![image](https://user-images.githubusercontent.com/49061096/141415035-40cd77f5-dea2-4c9d-bd76-9004708699f3.png)
   #### Method 2:
    * If the notification bar is not shown, right click on the requirements.txt and click on terminal as shown in the below picture.
      * Then, type in ``` pip install -r requirements.txt``` into the terminal
      * ![image](https://user-images.githubusercontent.com/49061096/141426278-e17cb154-87a1-4c8e-9c23-8644e96cdee7.png)
      
    #### Method 3:
     * If the notification bar is not shown, then open Project Settings/Preferences.
       * Go to Editor --> Inspections.
       * In the list of the inspections, select Unsatisfied package requirements.
       * Preview the list of the ignored requirements and click the Add icon (Add a package) to add them.
       * More details can be found at: https://www.jetbrains.com/help/pycharm/managing-dependencies.html#revert-ignored
    #### Method 4:
      * Navigate to preprocessing.py and hover over each library to install them.
        * ![image](https://user-images.githubusercontent.com/49061096/141426703-8bead3b4-dc28-48b4-99aa-763617a833d9.png)

     
5) Run the project.py in pycharm
6) When the login popup appear enter your username, password, database that you have created in the postgres system
7) Click on the login button 
8) Enter your sql query in the input panel (the first textbox)
9) Click on submit
10) To view the json file click on json file button
11) To view the QEP diagram click on Visualize button
