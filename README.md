# Merge-Sort-Algorithm

1)	Implement Mergesort algorithm; run the program on nine different arrays of real numbers, Array_1, Array_2, …, and Array_9; fill out the following table in a spreadsheet (named Mergesort_Time.xls(x) or Mergesort_Time.csv).
•	The size of Array_i should be no less than 1000 · i, but the actual array sizes are of your choice.
•	Elements in each array are also of your choice, and you are highly suggested to use the program to generate random real numbers.
•	The Excel spreadsheet needs to be automatically (i.e., by your program) filled out.
2)	Design an interface that allows the user to choose an arbitrary number i (the value of i is from 1 to 9). The interface will then display the original Array_i followed by the sorted Array_i.
3)	The interface will keep waiting for the user selection until the user chooses to exit.



This program is ran by first presenting the user with an interface which asked the user to select an array (1-9), and which ever number they select, will be the array that is chosen. The original array is then displayed, and then the sorted array is then displayed. The time is also calculated and displayed. The program must be re-run in order to first the unsorted array before seeing the sorted one. This is because once the array is sorted, it will remain sorted even after the user selects another array. All the information is then placed in a CSV spreadsheet file by the program. *Note* you must change the path to match your computer so that the program can create the CSV file on your computer. The excel spreadsheet is generated by the program.
