#!/bin/bash

TESTING_SCRIPT="./testing.sh"

echo -e "\033[1;34m-----------------------------------------------------------------------------------------------------------\033[0m"
echo -e "\033[1;33mTesting Door.wav\033[0m"
echo -e "\033[1;34m-----------------------------------------------------------------------------------------------------------\033[0m"
# testcase1
bash "$TESTING_SCRIPT" "12000" "2" "sound_addecho/door.wav" "sound_addecho/test.wav" "sound_addecho/door_12000_2.wav"
# testcase2
bash "$TESTING_SCRIPT" "12000" "4" "sound_addecho/door.wav" "sound_addecho/test.wav" "sound_addecho/door_12000_4.wav"
# testcase3
bash "$TESTING_SCRIPT" "20000" "4" "sound_addecho/door.wav" "sound_addecho/test.wav" "sound_addecho/door_20000_4.wav"
# testcase4
bash "$TESTING_SCRIPT" "35000" "2" "sound_addecho/door.wav" "sound_addecho/test.wav" "sound_addecho/door_35000_2.wav"
# testcase5
bash "$TESTING_SCRIPT" "60000" "1" "sound_addecho/door.wav" "sound_addecho/test.wav" "sound_addecho/door_60000_1.wav"
echo -e "\033[1;33mTesting short.wav\033[0m"
echo -e "\033[1;34m-----------------------------------------------------------------------------------------------------------\033[0m"
# testcase5
bash "$TESTING_SCRIPT" "3" "2" "sound_addecho/short.wav" "sound_addecho/test.wav" "sound_addecho/short_3_2.wav"