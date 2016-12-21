#!/bin/sh
ed $1 <<%
g/\/v0 /s//\/v0 ; /g
g/\/v1 /s//\/v1 ; /g
g/\/v2 /s//\/v2 ; /g
g/\/voob /s//\/voob ; /g
g/\/v0_a /s//\/v0_a ; /g
g/\/v0_b /s//\/v0_b ; /g
g/\/v0.1 /s//\/v0.1 ; /g
g/ Begin /s// ; /g
g/new_qa/s//new_QA/g
g/\/root/s///g
g/ -- /s// ; /g
w
%

