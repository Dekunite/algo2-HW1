- init:
    run: rm -f scheduler
    blocker: true

- build:
    run: g++ -std=c++11 -Wall -Werror data_structs.cpp scheduler.cpp -o scheduler  # timeout: 5
    blocker: true

- case1_given_with_hw:
   run: ./scheduler data.txt
   points: 10
   script:
        - expect: "process1 C"  # timeout: 1
        - expect: "process3 A"  # timeout: 1
        - expect: "process6 A"  # timeout: 1
        - expect: "process1 B"  # timeout: 1
        - expect: "process2 B"  # timeout: 1
        - expect: "process1 A"  # timeout: 1
        - expect: "process4 C"  # timeout: 1
        - expect: "process2 A"  # timeout: 1
        - expect: "process4 B"  # timeout: 1
        - expect: "process4 A"  # timeout: 1
        - expect: "process5 C"  # timeout: 1
        - expect: "process5 B"  # timeout: 1
        - expect: "process5 A"  # timeout: 1
        - expect: "Cumulative Lateness: 158"  # timeout: 1
        - expect: _EOF_  # timeout: 1
   return: 0
