SSID = "M112-PD"
SSID_PASSWORD = "aiv4aith2Zie4Aeg"

wifi.setmode(wifi.STATION)
wifi.sta.config({ssid=SSID, pwd=SSID_PASSWORD})
wifi.sta.autoconnect(1)

tmr.delay(5000000)

HOST = "d8zdah4wk5t8c.cloudfront.net"

-- sample_data = '{"username": "noob", "game_result": "t", "phone_number": "+17788469337"}'
data = '{"username": "'..username..'", "game_result": "'..game_result..'", "phone_number": "'..phone_number..'"}'


function build_post_request(host, payload)
    request = "POST / HTTP/1.1\r\n"..
    "Host: "..host.."\r\n"..
    "Connection: close\r\n"..
    "Content-Type: application/json\r\n"..
    "Content-Length: "..string.len(payload).."\r\n"..
    "\r\n"..
    payload

    print(request)
    return request
end

function display(sck,response)
    print(response)
end

function send_data(payload)
    socket = net.createConnection(net.TCP, 0)
    socket:on("receive", display)
    socket:connect(80, HOST)
    
    socket:on("connection", function(sck)
        post_request = build_post_request(HOST, payload)
        sck:send(post_request)
    end)
end
       
function main()
    ip = wifi.sta.getip()
    
    if(ip==nil) then 
        print("Connecting...")
    else
        tmr.create():stop(0)
        print("Connected!")
        print(ip)
        -- Send data
        send_data(data)
    end

end

-- tmr.create():alarm(5000, tmr.ALARM_SINGLE, main)
-- tmr.alarm(0,7000,1,main) 

if not tmr.create():alarm(5000, tmr.ALARM_SINGLE, main)
then
    print("whoopsie")
end