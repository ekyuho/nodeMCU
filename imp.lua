ssid = "myssid"
password = "mypassword"
host = '11.22.33.44'
port = '8000'
path = "/mypath?value="
ready = false

uart.setup(0, 9600, 8, 0, 1, 0)
uart.on("data", "\n", function(data)
  data = string.gsub(data, "[\r\n]", " ")
  call_server(data)
end, 0)  

wifi.setmode(wifi.STATION)
wifi.sta.config(ssid, password)
wifi.sta.autoconnect(1)

cnt = 1
tmr.alarm(3, 1000, 1, function() 
  if (wifi.sta.getip() == nil) and (cnt < 20) then 
    print("trying wifi AP..."..cnt.." sec")
    cnt = cnt + 1 
  else 
    tmr.stop(3)
    if (cnt < 20) then 
      ip = wifi.sta.getip();
      print("got wifi="..ip..", status="..wifi.sta.status());
      ready = true
    else node.restart()
    end
    cnt = nil;
  end
end)
  
function call_server(value)

  print("value="..value)
  if ready == false then return end
  
  conn=net.createConnection(net.TCP, 0) 
  conn:on("connection",function(conn, payload)
    conn:send("GET "..path..value.." HTTP/1.1\r\n".. 
      "Accept: */*\r\n"..
      "User-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Kyuho Kim;)\r\n"..
      "\r\n") 
  end)
  
  conn:on("receive", function(conn, payload) 
    print("Received: "..payload)
    conn:close();
  end)
    
  conn:connect(port, host) 
end
