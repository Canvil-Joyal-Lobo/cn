//4. Write a TCL Script to simulate working of multicasting routing protocol and analyze the throughput of the network

set ns [new Simulator -multicast on]
set tf [open mcast.tr w]
$ns trace-all $tf
set nm1 [open mcast.nam w]
$ns namtrace-all $nm1
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
$ns color 1 "red"
$ns color 2 "blue"
$ns duplex-link $n0 $n1 1.5Mb 10ms DropTail
$ns duplex-link $n0 $n2 1.5Mb 10ms DropTail
$ns duplex-link $n2 $n3 1.5Mb 10ms DropTail
set mproto DM
set mrthandle [$ns mrtproto $mproto {}]
set group1 [Node allocaddr]
set group2 [Node allocaddr]
set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
$udp0 set dst_addr_ $group1
$udp0 set dst_port_ 0
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp0
set udp1 [new Agent/UDP]
$ns attach-agent $n0 $udp1
$udp1 set dst_addr_ $group2
$udp1 set dst_port_ 0
set cbr2 [new Application/Traffic/CBR]
$cbr2 attach-agent $udp1
set rcvr1 [new Agent/Null]
$ns attach-agent $n1 $rcvr1
$ns at 1.0 "$n1 join-group $rcvr1 $group1"
set rcvr2 [new Agent/Null]
$ns attach-agent $n2 $rcvr2
$ns at 1.5 "$n2 join-group $rcvr2 $group2"
set rcvr3 [new Agent/Null]
$ns attach-agent $n3 $rcvr3
$ns at 2.0 "$n3 join-group $rcvr3 $group2"
$udp1 set class_ 1;
$udp0 set class_ 2;
$ns at 2.0 "$n3 join-group $rcvr2 $group2"
$ns at 0.5 "$cbr1 start"
$ns at 4.5 "$cbr1 stop"
$ns at 0.5 "$cbr2 start"
$ns at 4.5 "$cbr2 stop"
proc finish {} {
global ns tf nm1
$ns flush-trace
close $tf
close $nm1
exec nam mcast.nam &
exit 0
}
$ns at 5.0 "finish"
$ns run




////////////////////////////////////////////////////////////////


//mulrout.awk

BEGIN {count = 0;
time = 0;
}
{
if ($1 == "r") {
count += $6;
time = $2;
}
}
END {
system("clear");
printf("\n Total bytes transferred from sourec to destination is %d", count);
printf("\n Total simulation time %f",$2);
printf("\n Throughput: %f Mbps \n\n", (count/$2) * (8/1000000));
}
