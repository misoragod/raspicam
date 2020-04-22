#!/bin/bash

URL="https://maker.ifttt.com/trigger"
EVENTNAME="pi_motion_detect" 
YOUR_KEY="dppbgVv-3edRTHuGUoOe-Z" 

WEBHOOKSURL="${URL}/${EVENTNAME}/with/key/${YOUR_KEY}"
curl -X POST -H "Content-Type: application/json" -d \
    '{"value1":"'$1'","value2":"'$2'","value3":"'$3'"}' \
    ${WEBHOOKSURL} 

echo
exit 0
