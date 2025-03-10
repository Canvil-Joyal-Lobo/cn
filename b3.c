
//#3. Simulate to study transmission of packets over Ethernet LAN and determine the number of packets drop destination.

set ns [ new Simulator ]
set tr1 [ open b2.tr w ]
$ns trace-all $tr1
set nm1 [open b2.nam w ]
$ns namtrace-all $nm1

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]

$ns color 1 "blue"
$ns color 2 "red"
$ns duplex-link $n0 $n2 1Mb 200ms DropTail
$ns duplex-link $n1 $n2 1Mb 100ms DropTail
$ns duplex-link $n2 $n3 0.6Mb 100ms DropTail
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right
 
set lan [$ns newLan "$n3 $n4 $n5" 0.6Mb 40ms LL Queue/DropTail Mac/802_3 Channel]
$ns set queue-limit $n2 $n3 10
$ns duplex-link-op $n2 $n3 queuePos 10.0

set tcp1 [new Agent/TCP]
$ns attach-agent $n0 $tcp1
set sink1 [new Agent/TCPSink]
$ns attach-agent $n4 $sink1

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp1 set packetSize_ 500
$ftp1 set interval_ 0.005
$ns connect $tcp1 $sink1

set tcp2 [new Agent/TCP]
$ns attach-agent $n1 $tcp2
set sink2 [new Agent/TCPSink]
$ns attach-agent $n5 $sink2

set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$ftp2 set packetSize_ 500
$ftp2 set interval_ 0.001
$ns connect $tcp2 $sink2

$tcp1 set class_ 1
$tcp2 set class_ 2
$ns at 0.5 "$ftp1 start"
$ns at 4.9 "$ftp1 stop"
$ns at 1.0 "$ftp2 start"
$ns at 4.9 "$ftp2 stop"

proc finish {} {
global ns tr1 nm1
$ns flush-trace
exec nam b2.nam &
close $tr1
close $nm1
exit 0
}
$ns at 5.0 "finish"
$ns run


//dup.awk
BEGIN {
c=0;
c1=0
}
{
if($1=="d" && $9=="0.0" && $10 =="40")
c++;
if($1=="d" && $9=="1.0" && $10 n=="5.0")
c1++;
}
END{
printf("\n number of paclets dropped at the destination node4 %d",c);
printf("\n number of paclets dropped at the destination node5 %d",c1);
}
