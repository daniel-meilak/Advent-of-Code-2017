#!/bin/bash

for day in {01..25}
do
   if   [ $day -le 7  ]; then
      week=1
   elif [ $day -le 14 ]; then
      week=2
   elif [ $day -le 21 ]; then
      week=3
   else
      week=4
   fi

   cd week_${week}/day_${day}

   mv input input_${day}

   sed -i -r "s/\"input\"/\"input_${day}\"/g" day_${day}.cpp
   sed -i -r "s/\"input\"/\"input_${day}\"/g" day_${day}_v2.cpp
   sed -i -r "s/\"input\"/\"input_${day}\"/g" day_${day}_v3.cpp


   cd ../..
done