#Program 1: Simulate a three nodes point to point network with duplex links between them. Set the queue size and vary the bandwidth and find the number of packets dropped.

set ns [new Simulator]
set tf [open p1.tr w]
$ns trace-all $tf
set nm [open p1.nam w]
$ns namtrace-all $nm

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns color 1 "red"
$ns color 2 "green"
$n0 label "source"
$n1 label "source"
$n2 label "destination"

$ns duplex-link $n0 $n1 10mb 300ms DropTail
$ns duplex-link $n1 $n2 1mb 300ms DropTail

$ns set queue-limit $n0 $n1 10
$ns set queue-limit $n1 $n2 15

set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
set cbr1 [new Application/Traffic/CBR]
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.005
$cbr1 attach-agent $udp0

set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1
set cbr2 [new Application/Traffic/CBR]
$cbr2 set packetSize_ 500
$cbr2 set interval_ 0.005
$cbr2 attach-agent $udp1

set null1 [new Agent/Null]
$ns attach-agent $n2 $null1

$udp0 set class_ 1
$udp1 set class_ 2

$ns connect $udp0 $null1
$ns connect $udp1 $null1

proc finish {} {
    global ns tf nm
    exec nam p1.nam &
    $ns flush-trace
    close $tf
    close $nm
    exit 0
}

$ns at 0.1 "$cbr1 start"
$ns at 0.1 "$cbr2 start"
$ns at 10.0 "finish"
$ns run















#rd.awt

BEGIN{
	count=0;
}
{
	if($1=="r")
	count++;
}
END{
	printf("The Total Number of Packets Received Due to Congestion:%d\n\n",count);
}
