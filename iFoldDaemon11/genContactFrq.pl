#!/usr/bin/perl

$OUTPUT_UTIL_DIR = "outputUtil";

if (@ARGV<2) {
  print "Usage: genContactFrq.pl inputPDB inputMovie\n";
  exit;
}

# convert the output to frequency file
#print "$OUTPUT_UTIL_DIR/movie2freqs.linux $ARGV[1] $ARGV[0] 2 7.5 freq.out\n";
system("$OUTPUT_UTIL_DIR/movie2freqs.linux $ARGV[1] $ARGV[0] 2 7.5 freq.out");


#read the usual matix
open(IN, "<freq.out");
if(!IN){
  print "Unable to open input file\n";
 }
#$line=0;
$max = -10000;
$min =  10000;
#$var=0;
#$ivar=0;
$PI = 3.1415926;
$nCol = 2;

while (<IN>) {
  chomp($_);
  @tmp=split(" ",$_);
  my $i = $tmp[0];
  my $j = $tmp[1];
  if (abs($i-$j)>=0 && abs($tmp[$nCol])>0.01) {
    $matrix[$i][$j] = $tmp[$nCol];
    $matrix[$j][$i] = $tmp[$nCol];
    #$var+=abs($tmp[$nCol]);
    #$ivar++;
    if ($max<$matrix[$i][$j] ) {
      $max=$matrix[$i][$j];
    }
    if ($min>$matrix[$i][$j]) {
      $min=$matrix[$i][$j];
    }
  }
  else {
    $matrix[$i][$j]=0;
  }
}
close(IN);

$nres = system("grep \"CA  \" $ARGV[0] | wc -l");

#$nres = $ARGV[2];
#print $max . " " . $min . "\n";

$max = 1;
$min = 0;
#$var/=$ivar;
#feed in the PDB file and create the contact map
$cutoff = 7.5;
open(IN, "< $ARGV[0]");
$nres = 0;
while ((<IN>)) {
  if (substr($_, 0, 6) eq "ATOM  ") {
    $atom = substr($_, 12, 3);
    $res  = substr($_, 17, 3);
    if ($atom eq " CB" || ($atom eq " CA" && $res eq "GLY")) {
      $coor = substr($_, 30, 24);
      @xyz = split(" ", $coor);
      for ($i=0; $i<3; $i++) {
        $CB[$nres][$i] = $xyz[$i];
      }
      $nres++;
    }
  }
}
close(IN);
for ($i=0; $i<$nres; $i++) {
  for ($j=0; $j<$i-1; $j++) {
    if (distance($i, $j) < $cutoff) {
      $matrix[$i][$j]=-1;
    }
    else {
      $matrix[$i][$j]=0;
    }
  }
}

for ($i=0; $i<$nres; $i++) {
  for ($j=0; $j<$nres; $j++) {
    if (!defined($matrix[$i][$j])) {
      $matrix[$i][$j]=0;
    }
  }
}
$dim = $nres;

#for ($i=0;$i<$dim; $i++) {
#  for ($j=0; $j<$dim; $j++) {
#    if (abs($i-$j)<2) {
#      print  "0 ";
#    }
#    else {
#      print $matrix[$i][$j] . " " ;
#    }
#  }
#  print "\n";
#}

createPS();

sub distance{
  my($dist) = 0;
  my($ires) = $_[0];
  my($jres) = $_[1];
  my($i)=0;
  for ($i=0; $i<3; $i++) {
    $dist += ($CB[$ires][$i]-$CB[$jres][$i])*($CB[$ires][$i]-$CB[$jres][$i]);
  }
  return sqrt($dist);
}

sub createPS{
  open(IN, ">freq.eps");
  print IN "%!PS-Adobe-2.0 EPSF-1.2\n";
  print IN "%%Pages: 1\n";
  print IN "%%BoundingBox: 0 0 220 220\n";
  print IN "/d {10} def\n";
  print IN "/R {45} def\n";
  print IN "/FS {R 1.2 div} def\n";
  print IN "/box{\n";
  print IN "setrgbcolor\n";
  print IN "/y exch def\n";
  print IN "/x exch def\n";
  print IN "newpath \n";
  #print IN "x d 2 div sub y d 2 div sub moveto\n";
  print IN "x y moveto\n";
  print IN "d 0 rlineto\n";
  print IN "0 d rlineto\n";
  print IN "d -1 mul 0 rlineto\n";
  print IN "0 d -1 mul rlineto\n";
  print IN "fill\n";
  print IN "} def\n";
  print IN "/wbox{\n";
  print IN "setrgbcolor\n";
  print IN "/y exch def\n";
  print IN "/x exch def\n";
  print IN "newpath\n";
  print IN "x y moveto\n";
  print IN "d 2 mul 0 rlineto\n";
  print IN "0 d rlineto\n";
  print IN "d -2 mul 0 rlineto\n";
  print IN "0 d -1 mul rlineto\n";
  print IN "fill\n";
  print IN "} def\n";
  print IN "0.06 0.06 scale\n";
  print IN "gsave\n";
  print IN "100 100 translate\n";

  printf("$max $min\n");
  for (my $i=0; $i<$dim; $i++) {
    for (my $j=0; $j<$dim; $j++) {
      my $x = int(10*$i);
      my $y = int(10*$j);
      my $color=$matrix[$i][$j];
      if ($j>$i) {
	if ($color!=0) {
	  my $r=0;
	  my $g=0;
	  my $b=0;
	  #if ($min<0 && $max>0) {
	  if ($color<0) {
	    $r=cos($color/$min*$PI/2.0);
	    $g=cos($color/$min*$PI/2.0);
	    $b=sin(($color/$min)*$PI/2.0);
	  }
	  else {
	    $r = 1;
	    $g = 1-$color/$max;
	    $b = 0;
	    #$r = 1-$color/$max;
	    #$g = 1-$color/$max;
	    #$b = 1-$color/$max;
	  }
	  #}
	  #else{
	  #  $r = 1;
	  #  $g = 1-$color/$max;
	  #  $b = 0;
	  #}
	  print IN "$y $x $r $g $b box\n";
	}
      }
      else {
	if ($color==-1) {
	  print IN "$y $x 0 0 0 box\n"
	}
      }
    }
  }
  $step = ($max-$min)/100;
  print IN "gsave\n";
  print IN "0 0 0 setrgbcolor\n";
  print IN "/Helvetica-Bold findfont FS scalefont setfont\n";
  $x = $dim*10+80;
  $y = -10;
  printf IN ("%d $y moveto\n", $x);
  printf IN ("(%.2f) show\n",$min);
  if ($min<0) {
    $y = (0-$min)/($max-$min)*100*10-20;
    print IN "$x $y moveto\n";
    printf IN ("(%.2f) show\n",0);
  }
  $y = 100*2-20;
  print IN "$x $y moveto\n";
  printf IN ("(%.2f) show\n",$max);
  print IN "grestore\n";
  for (my $i=0; $i<100; $i++) {
    my $x = $dim*10+50;
    my $y = $i*2;
    $color=$min+$step*$i;
    my $r=0;
    my $g=0;
    my $b=0;
    if ($color<0) {
      $r=cos($color/$min*$PI/2.0);
      $g=cos($color/$min*$PI/2.0);
      $b=sin(($color/$min)*$PI/2.0);
    }
    else {
      $r = 1;
      $g = 1-$color/$max;
      $b = 0;
      #$r = 1-$color/$max;
      #$g = 1-$color/$max;
      #$b = 1-$color/$max;
    }
    print IN "$x $y $r $g $b wbox\n";
  }
  print IN "grestore\n";


  #x-axis:lowwer
  print IN "gsave\n";
  print IN "100 100 translate\n";
  print IN "/i {0} def\n";
  print IN "/str 5 string def\n";
  print IN "1 1 " .  $dim . "{\n";
  print IN "/i i 1 add def\n";
  print IN "0 0 moveto 10 0 lineto\n";

  print IN "i 10 eq \{\n";
  print IN "/i i 10 sub def\n";
  print IN "10 10 lineto\n";
  print IN "gsave\n";
  print IN "/Helvetica-Bold findfont FS scalefont setfont\n";
  print IN "-10 -40 moveto\n";
  print IN "dup str cvs\n";
  print IN "str show\n";
  print IN "grestore\n";
  print IN "}{\n";

  print IN "}ifelse\n";
  print IN "10 0 translate\n";
  print IN "}for\n";
  print IN "stroke\n";
  print IN "grestore\n";
  #x-axis: upper
  
  print IN "gsave\n";
  print IN "100 100 " . $dim . " 10 mul add translate\n";
  print IN "/i {0} def\n";
  print IN "1 1 " .  $dim . "{\n";
  print IN "/i i 1 add def\n";
  print IN "0 0 moveto 10 0 lineto\n";
  print IN "i 10 eq \{\n";
  print IN "/i i 10 sub def\n";
  print IN "10 -10 lineto\n";
  #print IN "gsave\n";
  #print IN "/Helvetica-Bold findfont FS scalefont setfont\n";
  #print IN "-10 -40 moveto\n";
  #print IN "dup str cvs\n";
  #print IN "str show\n";
  #print IN "grestore\n";
  print IN "}{\n";

  print IN "}ifelse\n";
  print IN "10 0 translate\n";
  print IN "}for\n";
  print IN "stroke\n";
  print IN "grestore\n";

  #y-axis: left
  print IN "gsave\n";
  print IN "100 100 translate\n";
  print IN "/i {0} def\n";
  print IN "/j {0} def\n";
  print IN "/str 5 string def\n";
  print IN "1 1 " .  $dim . "\{\n";
  print IN "/i i 1 add def\n";
  print IN "/j j 1 add def\n";
  print IN "0 0 moveto 0 10 lineto\n";
  print IN "i 10 eq \{\n";
  print IN "/i i 10 sub def\n";
  print IN "10 10 lineto\n";
  print IN "gsave\n";
  print IN "90 rotate\n";
  print IN "/Helvetica-Bold findfont FS scalefont setfont\n";
  print IN "-10 20 moveto\n";
  print IN "j str cvs\n";
  print IN "str show\n";
  print IN "grestore\n";
  print IN "}{\n";
  print IN "}ifelse\n";
  print IN "0 10 translate\n";
  print IN "}for\n";
  print IN "stroke\n";
  print IN "grestore\n";

  #y-axis: right
  print IN "gsave\n";
  print IN "100 " . $dim . " 10 mul add 100 translate\n";
  print IN "/i {0} def\n";
  print IN "/j {0} def\n";
  print IN "/str 5 string def\n";
  print IN "1 1 " .  $dim . "\{\n";
  print IN "/i i 1 add def\n";
  print IN "/j j 1 add def\n";
  print IN "0 0 moveto 0 10 lineto\n";
  print IN "i 10 eq \{\n";
  print IN "/i i 10 sub def\n";
  print IN "-10 10 lineto\n";
  #print IN "gsave\n";
  #print IN "90 rotate\n";
  #print IN "/Helvetica-Bold findfont FS scalefont setfont\n";
  #print IN "-10 20 moveto\n";
  #print IN "j str cvs\n";
  #print IN "str show\n";
  #print IN "grestore\n";
  print IN "}{\n";
  print IN "}ifelse\n";
  print IN "0 10 translate\n";
  print IN "}for\n";
  print IN "stroke\n";
  print IN "grestore\n";

  print IN "showpage";
  close(IN);
}
