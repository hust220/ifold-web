#!/usr/bin/perl

use lib(/afs/isis.unc.edu/home/i/f/ifold/ifoldwww/iFoldDaemon.new);
use IPC::Run;
use LSF::Job;

my $job = LSF::Job->submit(-q => ' ', -o => '/dev/null', "echo hello");
	
