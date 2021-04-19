# Vaccine-Monitor
The 1st Project created for The System Programming class.

[System-Implentation.pdf](https://github.com/mixo091/Vaccine-Monitor/files/6338612/System-Implentation.pdf)



#This is the 1st Project On System Programming 2021.

Vaccine Monitor is a data system implemented to keep Record of vaccinated and non-vaccinated  citizens for different viruses.
The data structures that impemented the System are in DataStructures.cpp and SpeciasData.cpp files.
In orden to maximize the the efficiency of the programm we use a vaccinated_SkipList  and a non_vaccinated_Skiplist and a Bloomfilter for each virus.
The SkipLists.
The Skipslists are special data structures which in this case keep for each virus the [ids] and [pointers to citizens] which are 
vaccinated or non vaccinated respectively.(in the vaccinated list we have a also a pointer to the date of vaccination)
The Bloomfilters.
Each virus has also a bloomFilter which is used by the system in order to answer quickly if a citizen is not Vaccinated.
The system is implemented using a List in which each node keeps the data of a Specific virus ,its name ,its SkipLists and BloomFilters.
In Addition to those Structures we have a Record List and a CountryList to avoid Data duplication.At every connection to the other 
structures  we use point reference to Record and Countries.
The Vaccine monitor gets an input Record file an the size of the blomm filter.
ex.. ./VaccineMonitor -c input0.txt -b 8000
The System now keeps all the input Records and we have impemented some Queries that can be done to the system 
in orden to get information and make changes .
The system use its data Strusture efficiently to implement the Queries.


Implemented queries implemented in ProgrammFunctionality.cpp.

● /vaccineStatusBloom citizenID virusName 
H εφαρμογή θα ελέγχει το bloom filter που σχετίζεται με virusName και θα τυπώνει μήνυμα για το αν ο 
πολίτης με αριθμό ταυτότητας citizenID έχει κάνει το εμβόλιο κατά του virusName. (Δείτε παρακάτω 
αναλυτικά τις δομές που θα πρέπει να κρατάτε). 
Output format: 
 NOT VACCINATED OR 
 MAYBE 
● /vaccineStatus citizenID virusName
H εφαρμογή θα ελέγχει τη skip list που σχετίζεται με virusName και θα τυπώνει μήνυμα για το αν ο πολίτης 
με αριθμό ταυτότητας citizenID έχει κάνει το εμβόλιο κατά του virusName. 
Output format: 
 NOT VACCINATED OR 
 VACCINATED ON 27-12-2020
● /vaccineStatus citizenID 
H εφαρμογή θα ελέγχει όλες τις skip lists (μία για κάθε ίωση), θα εντοπίζει όλες τις εγγραφές του πολίτη με 
αριθμό ταυτότητας citizenID, και θα τυπώνει για κάθε ίωση αν έχει εμβολιαστεί και την ημερομηνία 
εμβολιασμού. 
Output format: μια γραμμή για κάθε ίωση. Παράδειγμα: 
COVID-19 YES 27-12-2020 
SARS-1 NO 
H1N1 YES 11-11-2020 
● /populationStatus [country] virusName date1 date2 
Αν δεν δοθεί country όρισμα, η εφαρμογή θα τυπώνει για την ασθένεια virusName τον αριθμό πολιτών 
σε κάθε χώρα που έχουν εμβολιαστεί μέσα στο διάστημα [date1...date2] και το ποσοστό του πληθυσμού 
της χώρας που έχει εμβολιαστεί. Αν δοθεί country όρισμα, η εφαρμογή θα τυπώνει για την ασθένεια 
virusName, τον αριθμό πολίτων που έχουν εμβολιαστεί και το ποσοστό του πληθυσμού της χώρας που έχει 
εμβολιαστεί μέσα στο διάστημα [date1...date2]. Εάν υπάρχει ο ορισμός για date1 θα πρέπει να 
υπάρχει και ορισμός για date2, αλλιώς, θα τυπώνεται το μήνυμα λάθους ERROR στον χρήστη.
 Output format: μια γραμμή για κάθε χώρα. Παράδειγμα όπου δεν έχει δοθεί country όρισμα: GREECE 523415 5.02% 
USA 358000000 10.8% 
ISRAEL 3289103 38.0% 
● /popStatusByAge [country] virusName date1 date2 
Αν δεν δοθεί country όρισμα, η εφαρμογή θα τυπώνει για την ασθένεια virusName τον αριθμό 
εμβολιασμών ανά ηλικιακή κατηγορία σε κάθε χώρα και το ποσοστό του πληθυσμού της ηλικιακής κατηγορίας 
που έχει εμβολιαστεί μέσα στο διάστημα [date1...date2]. Αν δοθεί country όρισμα, η εφαρμογή θα 
τυπώνει για την ασθένεια virusName, τον αριθμό εμβολιασμών ανά ηλικιακή κατηγορία και το ποσοστό 
του πληθυσμού της ηλικιακής κατηγορίας που έχει εμβολιαστεί μέσα στο διάστημα [date1...date2] στη 
χώρα country. Εάν υπάρχει ο ορισμός για date1 θα πρέπει να υπάρχει και ορισμός για date2, αλλιώς, 
θα τυπώνεται το μήνυμα λάθους ERROR στον χρήστη.
Output format: Παράδειγμα όπου δεν έχει δοθεί country όρισμα: 
GREECE 
0-20 0 0% 
20-40 18795 0.36% 
40-60 64650 1.24% 
60+ 439970 8.44% 
ISRAEL 
0-20 0 15% 
20-40 18795 23% 
40-60 64650 32.24% 
60+ 4399070 90.44% 
● /insertCitizenRecord citizenID firstName lastName country age virusName YES/NO 
[date] 
H εφαρμογή θα εισάγει στο bloom filter και στη κατάλληλη skip list που σχετίζεται με την ίωση virusName 
μια νέα εγγραφή με τα στοιχεία της. Μόνο το YES συνοδεύεται από ένα date. Αν ο πολίτης με αριθμό 
ταυτότητας citizenID έχει ήδη εμβολιαστεί κατά του ιού virusName η εφαρμογή επιστρέφει: 
ERROR: CITIZEN 889 ALREADY VACCINATED ON 27-12-2020
● /vaccinateNow citizenID firstName lastName country age virusName 
Η εφαρμογή ελέγχει αν ο πολίτης με αριθμό ταυτότητας citizenID έχει ήδη εμβολιαστεί κατά του ιού 
virusName και αν ναι, επιστρέφει: 
ERROR: CITIZEN 889 ALREADY VACCINATED ON 27-12-2020. 
Αν δεν έχει εμβολιαστεί, η εφαρμογή εισάγει στο bloom filter και στη κατάλληλη skip list που σχετίζεται με 
την ίωση virusName την εγγραφή: 
citizenID firstName lastName country age virusName YES todays_date όπου todays_date 
είναι η σημερινή ημερομηνία. 
● /list-nonVaccinated-Persons virusName 
H εφαρμογή θα προσπελάζει την κατάλληλη skip list που σχετίζεται με την ίωση virusName και θα τυπώνει
όλους τους πολίτες που δεν έχουν εμβολιαστεί κατά της virusName. Συγκεκριμένα, θα τυπώνει 
citizenID, firstName, lastName, country και age. 
Output format: μια γραμμή για κάθε πολίτη. Παράδειγμα: 
125 Jon Dupont USA 76 
889 John Papadopoulos GREECE 52
 ● /exit 
Έξοδος από την εφαρμογή
##############################################################################


If you want to Generate your own input file ,a bash Script is impemented for this cause.

./RecordGen.sh [VirusFile] [CountryFile] [numberOFlines] [do you want Duplications (1) or not (0)] 
//To create a test file
ex..
cd bashScript
./RecordGen.sh Virus.txt Countries.txt 100000 0
###############################################################################

Example of execution And queries.
EXECUTION 

//to run the programm
cd ProjectS1
make
./VaccineMonitor -c input0.txt -b 8000

------------------------------------------------------------------------------------

QUERIES

/popByAge SARS-1 CANADA 10-2-2002 30-6-2022
/popByAge ECHOVIRUS CANADA 10-2-2002 30-6-2022
/popByAge  HEPATITIS-C USA 20-5-2000 30-9-2022
/popByAge HEPATITIS-A BULGARIA 8-12-2006 20-6-2019

/populationStatus SARS-1 20-5-2001 4-8-2020
/populationStatus MERS-CORONAVIRUS 20-5-2001 4-8-2019
/populationStatus H1N1 20-5-2011 4-8-2019
/populationStatus ROTAVIRUS-B 20-5-2001 4-8-2017
/populationStatus SPANISHFLU 20-5-2011 4-8-2019

/vaccineStatus 833
/vaccineStatusBloom 833 HEPATITIS-A 
/vaccinateNow 833 SCARLETT Peterson  SOUTHAFRICA  31 HEPATITIS-A 
/vaccineStatus 833
/vaccineStatusBloom 833 HEPATITIS-A 
/vaccineStatusBloom 833 ROTAVIRUS-B
/vaccinateNow 833 SCARLETT Peterson  SOUTHAFRICA 31 ROTAVIRUS-B
/vaccineStatusBloom 833 ROTAVIRUS-B

/vaccinateNow 669 MONICA Thomas  HOLLAND  55 ADENOVIRUS
/vaccinateNow 669 MONICA Thomas  HOLLAND  55 ADENOVIRUS
/vaccinateNow 833 SCARLETT Peterson  SOUTHAFRICA  31 HEPATITIS-A 
/vaccineStatusBloom 833 HEPATITIS-A 
/vaccineStatusBloom 833 COVID-19
/vaccineStatus 833 HEPATITIS-A
/vaccineStatus 833 COVID-19
/vaccinateNow 833 SCARLETT Peterson  SOUTHAFRICA  31 COVID-19
/vaccinateNow 833 SCARLETT Peterson  SOUTHAFRICA  31 SARS-1
/vaccinateNow 833 SCARLETT Peterson  SOUTHAFRICA  31 SARS-1


/populationStatus SARS-1 20-5-2001 4-8-2020
/populationStatus MERS-CORONAVIRUS 20-5-2001 4-8-2019
/populationStatus MERS-CORONAVIRUS 20-5-2011 4-8-2019
/insertCitizenRecord 10203 gerarld louo CANADA 24 COVID-19 NO
/vaccinateNow  10203 gerarld louo CANADA 24 COVID-19
/vaccinateNow 10203 gerarld louo CANADA 24 SARS-1
/vaccineStatusBloom 833 ROTAVIRUS-B
/vaccineStatus 10203 ADENOVIRUS
/vaccineStatusBloom 1023 ROTAVIRUS-B
/vaccinateNow  10203 gerarld louo CANADA 24 ADENOVIRUS
/vaccinateNow  10203 gerarld louo CANADA 24 ADENOVIRUS

###################################################################################################################################

