function startup()
    print('in startup')
    dofile('imp.lua')
    end
tmr.alarm(0,1500,0,startup)
