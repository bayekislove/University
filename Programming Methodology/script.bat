@echo off
setlocal enableDelayedExpansion
FOR /l %%N in (1,1,14) do (
    set "NUM=%%N"
    set "DIRNAME=pracownia!NUM!"
    md !DIRNAME!
)