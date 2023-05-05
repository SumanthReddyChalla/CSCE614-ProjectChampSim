
my $line = "";

my %fields_hash = ();

my @fields_ordered = ();

my @contents = ();

sub unique_sort(@);

while($line = <STDIN>) {
	chomp($line);
	if ($line =~ /CPU 0 cumulative IPC|L1D TOTAL|L1D AVERAGE MISS|cpu0_L1D PREFETCH  REQUESTED/) {
		@contents = split (" ",$line);
		for (my $i = 0; $i <= $#contents; $i++) {
			if ($contents[$i] =~ /:\s*$/) {
				$contents[$i] =~ s/://g;
				$fields_hash{$contents[$i]} = $contents[$i+1];
				push(@fields_ordered,$contents[$i]);
			}
		}
	}

}

@fields_ordered = unique_sort(@fields_ordered);
foreach my $i (@fields_ordered) {
	print "$fields_hash{$i},";
}
print "\n";

sub unique_sort (@) {
	my %tmp = (); my @return_list = ();
	foreach my $i (@_) {
		unless (exists $tmp{$i}) {
			$tmp{$i} = 1;
			push(@return_list,$i);
		}
	}
	return @return_list;
}

