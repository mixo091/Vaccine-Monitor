#!/bin/bash



	echo "VirusFile: $1";
	echo "Countryfile: $2";
        echo "numberOfLines: $3";
        echo "DuplicatesAllowed: $4";
	echo "Generating Record File!"
	file="InputFile.txt"
	if [ -f "$file" ] ; then
    	rm "$file"
	fi
	sleep 1
	echo "..."
	sleep 1
	echo "..."
	sleep 1
	#--------------------------------------------------------
	duplicates=$4
	
	IdRange=10000
	AgeRange=100
	MonthRange=12
	DayRange=30
	yearRange=21
	vaccinatedRange=2
	id=0
    age=0
    Indexid=0
	echo "Records to be Created: ${numOflines}"
	#Read Countries.
	countries=()
	while IFS= read -r line; do
	   countries+=("$line")
	done <$2
	#Read Viruses.
	Viruses=()
	while IFS= read -r line; do
	   Viruses+=("$line")
	done <$1
	#Read Names
	Names=()
	while IFS= read -r line; do
	   Names+=("$line")
	done <names.txt
	#Read Surnames
	Surnames=()
	while IFS= read -r line; do
	   Surnames+=("$line")
	done <surnames.txt

	#-------------------------------
	#Create Random Record.
	countriesRange=${#countries[@]}
	VirusesRange=${#Viruses[@]}
	NamesRange=${#Names[@]}
	SurnamesRange=${#Surnames[@]}
	lines=1
	echo "$numOflines random Records:"
	echo "---------------------------"
	if [ $duplicates -eq 1 ]
	then
		
    	while [ "$lines" -le $3 ]      
		do
			
			id=$RANDOM	
			age=$RANDOM
			day=$RANDOM
			month=$RANDOM
			year=$RANDOM
			country=$RANDOM
			Virus=$RANDOM
			name=$RANDOM
			surname=$RANDOM
			vaccinated=$RANDOM



			let "id %= $IdRange"
			let "month %= $MonthRange"
			let "day %= $DayRange"
			let "year %=yearRange"
			let "country %= $countriesRange"
			let "age %= $AgeRange"
			let "Virus %= $VirusesRange"
			let "name %= $NamesRange"
			let "surname %= $SurnamesRange"
			let "vaccinated %= $vaccinatedRange"
		    #Record1=" ${Names[$name]} ${Surnames[$surname]} "
		    if [ $vaccinated -eq 0 ]
			then
			Record="$id ${Names[${name}]} ${Surnames[$surname]}  ${countries[$country]}  $age ${Viruses[$Virus]} NO"
			fi
			if [ $vaccinated -eq 1 ]
			then
			if [ 10 -gt $year ]
			then
			Record="$id ${Names[${name}]} ${Surnames[$surname]} ${countries[$country]} $age ${Viruses[$Virus]} YES $day-$month-200$year"
		    fi
		    if [ $year -gt 10 ]
			then
			Record="$id ${Names[${name}]} ${Surnames[$surname]} ${countries[$country]} $age ${Viruses[$Virus]} YES $day-$month-20$year"
		    fi
			fi
		    #NAME>Input1.txt
		   # echo "$Record"
		   
		
			echo "$Record">>InputFile.txt

	  		let "lines += 1"  # Increment count.
		done
	fi

	if [ $duplicates -eq  0 ]
	then
		ids=($(seq 0 1 $IdRange))
			#printf "%s\n" "${ids[@]}"
			echo "${#ids[@]}"
			MovingRange=${#ids[@]}
			let "MovingRange -= 1"
			echo "$MovingRange"

	
	    while [ "$lines" -le $3 ]      
		do
			Indexid=$RANDOM
			let "Indexid %= $MovingRange"
			

			#-------------------------------------------------------------------------------	
			age=$RANDOM
			day=$RANDOM
			month=$RANDOM
			year=$RANDOM
			country=$RANDOM
			Virus=$RANDOM
			name=$RANDOM
			surname=$RANDOM
			vaccinated=$RANDOM
			let "month %= $MonthRange"
			let "day %= $DayRange"
			let "year %=yearRange"
			let "country %= $countriesRange"
			let "age %= $AgeRange"
			let "Virus %= $VirusesRange"
			let "name %= $NamesRange"
			let "surname %= $SurnamesRange"
			let "vaccinated %= $vaccinatedRange"
		    #Record1=" ${Names[$name]} ${Surnames[$surname]} "
		    if [ $vaccinated -eq 0 ]
			then
			Record="${ids[$Indexid]} ${Names[${name}]} ${Surnames[$surname]}  ${countries[$country]}  $age ${Viruses[$Virus]} NO"
			fi
			if [ $vaccinated -eq 1 ]
			then
			if [ 10 -gt $year ]
			then
			Record="${ids[$Indexid]} ${Names[${name}]} ${Surnames[$surname]} ${countries[$country]} $age ${Viruses[$Virus]} YES $day-$month-200$year"
		    fi
		    if [ $year -gt 10 ]
			then
			Record="${ids[$Indexid]} ${Names[${name}]} ${Surnames[$surname]} ${countries[$country]} $age ${Viruses[$Virus]} YES $day-$month-20$year"
		    fi
			fi
		    #echo "$Record"
			echo "$Record">>InputFile.txt
			#-------------------------------------------------------------------------------
			ids[$Indexid]=${ids[$MovingRange]}
			let "MovingRange =MovingRange-1"
			if [ $MovingRange -eq 1 ]; then
				echo "No more unique identifiers available."
				break
			fi
			let "lines += 1"
		done
    fi
	echo "________TestRecordFile is generated________"


	
