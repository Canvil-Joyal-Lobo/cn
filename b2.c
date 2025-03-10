#2. Simulate the network with five nodes n0, n1, n2, n3, n4, forming a star topology. The node

set ns [new Simulator]

set nf [open star.nam w]

$ns namtrace-all $nf


set tf [open star.tr w]

$ns trace-all $tf


set n0 [$ns node]

set n1 [$ns node]

set n2 [$ns node]

set n3 [$ns node]

set n4 [$ns node]


$n0 label "TCP source"

$n3 label "TCP Destination"

$n1 label "UDP Source"

$n2 label "UDP Destination"


$n0 shape square

$n3 shape square

$n4 shape circle

$n1 shape hexagon

$n2 shape hexagon


$n0 color "green"

$n3 color "red"

$n1 color "green"

$n2 color "red"

$n4 color "black"

$ns color 1 "red"

$ns color 2 "blue"


$ns duplex-link $n0 $n4 1Mb 10ms DropTail

$ns duplex-link $n1 $n4 1Mb 10ms DropTail

$ns duplex-link $n2 $n4 1Mb 10ms DropTail

$ns duplex-link $n3 $n4 1Mb 10ms DropTail


set tcp0 [new Agent/TCP]

$ns attach-agent $n0 $tcp0

set sink0 [new Agent/TCPSink]

$ns attach-agent $n3 $sink0


set udp0 [new Agent/UDP]

$ns attach-agent $n1 $udp0


set null0 [new Agent/Null]

$ns attach-agent $n2 $null0


$udp0 set class_ 1

$tcp0 set class_ 2


$ns connect $tcp0 $sink0

$ns connect $udp0 $null0


set cbr0 [new Application/Traffic/CBR]

$cbr0 attach-agent $udp0

$cbr0 set PacketSize_ 500

$cbr0 set interval_ 0.01


set ftp0 [new Application/FTP]

$ftp0 attach-agent $tcp0


$ns at 0.5 "$ftp0 start"

$ns at 9.5 "$ftp0 stop"

$ns at 1.0 "$cbr0 start"

$ns at 9.9 "$cbr0 stop"


proc finish {} {

global ns nf tf

close $tf

close $nf

exec nam star.nam & }

$ns at 10.0 "finish"

$ns run   
