#Program 5: Simulate the different types of internet traffic such as FTP and TELNET over a wired network and analyze the packet drop and packet delivery ratio in the network.

set ns [new Simulator]

set tf [open ftp.tr w]
$ns trace-all $tf

set nm [open ftp.nam w]
$ns namtrace-all $nm

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

$ns color 1 "red"
$ns color 2 "green"

$ns duplex-link $n0 $n2 0.3Mb 10ms DropTail
$ns duplex-link $n1 $n2 0.3Mb 10ms DropTail
$ns duplex-link $n2 $n3 0.3Mb 10ms DropTail
$ns duplex-link $n2 $n4 0.3Mb 10ms DropTail

$ns set queue-limit $n0 $n2 5
$ns set queue-limit $n1 $n2 5
$ns set queue-limit $n2 $n3 5
$ns set queue-limit $n2 $n4 5

set tcp1 [new Agent/TCP]
$ns attach-agent $n0 $tcp1

set sink1 [new Agent/TCPSink]
$ns attach-agent $n3 $sink1

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp1 set packetSize_ 500
$ftp1 set interval_ 0.005
$ns connect $tcp1 $sink1

set tcp2 [new Agent/TCP]
$ns attach-agent $n1 $tcp2

set sink2 [new Agent/TCPSink]
$ns attach-agent $n3 $sink2

set telneto [new Application/Telnet]
$telneto attach-agent $tcp2
$telneto set packetSize_ 500
$telneto set interval_ 0.005
$ns connect $tcp2 $sink2

set tcp3 [new Agent/TCP]
$ns attach-agent $n4 $tcp3

set sink3 [new Agent/TCPSink]
$ns attach-agent $n3 $sink3

set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp3
$ftp2 set packetSize_ 500
$ftp2 set interval_ 0.005
$ns connect $tcp3 $sink3

$tcp1 set class_ 1
$tcp2 set class_ 2

proc finish {} {
	global ns tf nm
	exec nam ftp.nam &
	$ns flush-trace
	close $tf
	close $nm
	exit 0
}

$ns at 0.1 "$ftp1 start"
$ns at 0.1 "$ftp2 start"
$ns at 0.1 "$telneto start"
$ns at 5.0 "finish"

$ns run




































#code.awk 
BEGIN {
	drop = 0;
	sent = 0;
	rec = 0;
	ratio = 0;
}

{
	if ($1 == "d")
    	drop++;
	if ($1 == "+")
    	sent++;
	if ($1 == "r")
    	rec++;
	ratio = (rec / sent) * 100;
}

END {
	printf("\nTotal number of packets sent from source: %d", sent);
	printf("\nTotal number of packets received at destination: %d", rec);
	printf("\nTotal number of packets dropped: %d", drop);
	printf("\nPacket delivery ratio: %f\n", ratio);
}
