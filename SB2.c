#Program 2: Simulate the network with five nodes n0, n1, n2, n3, n4, forming a star topology. The node n4 is at the center. Node n0 is a TCP source, which transmits packets to node n3 (a TCP sink) through the node n4. Node n1 is another traffic source, and sends UDP packets to node n2 through n4. The duration of the simulation time is 10 seconds.

set ns [new Simulator]

set tr1 [open b2.tr w]
$ns trace-all $tr1

set nm1 [open b2.nam w]
$ns namtrace-all $nm1

# Create nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

# Label nodes
$n0 label "TCPSOURCE"
$n1 label "UDPSOURCE"
$n2 label "UDPDESTINATION"
$n3 label "TCPDESTINATION"
$n4 label "ROUTER"

# Color and shape configuration
$ns color 1 "blue"
$ns color 2 "red"
$n0 color "green"
$n3 color "green"
$n1 color "orange"
$n2 color "orange"
$n4 shape square

# Duplex links with configuration
$ns duplex-link $n0 $n4 1Mb 20ms DropTail
$ns duplex-link $n1 $n4 1Mb 20ms DropTail
$ns duplex-link $n4 $n2 1Mb 20ms DropTail
$ns duplex-link $n4 $n3 1Mb 20ms DropTail

# Link orientations
$ns duplex-link-op $n0 $n4 orient left-up
$ns duplex-link-op $n1 $n4 orient right-up
$ns duplex-link-op $n4 $n2 orient right-up
$ns duplex-link-op $n4 $n3 orient left-up

# TCP setup
set tcp1 [new Agent/TCP]
$ns attach-agent $n0 $tcp1

set sink1 [new Agent/TCPSink]
$ns attach-agent $n3 $sink1

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
set packetSize_ 500
$ftp1 set interval_ 0.005
$ns connect $tcp1 $sink1

# UDP setup
set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1

set null1 [new Agent/Null]
$ns attach-agent $n2 $null1
$ns connect $udp1 $null1

set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.005

# Class setup
$tcp1 set class_ 1
$udp1 set class_ 2

# Start and stop events
$ns at 0.5 "$ftp1 start"
$ns at 9.5 "$ftp1 stop"
$ns at 1.0 "$cbr1 start"
$ns at 9.9 "$cbr1 stop"

# Finish procedure
proc finish { } {
	global ns tr1 nm1

	$ns flush-trace
	exec nam b2.nam &
	close $tr1
	close $nm1
	exit 0
}

$ns at 10.0 "finish"
$ns run
