# hextools

These are tools to do what hex editors do.

I don't really want to install any hex editors, and rather than looking at sane
packages out there with flags and whatnot, it came to me that I didn't know how
to do this kind of thing if not in C.

	hexout :: outputs files in hexadecimal pairs
	hexin  :: reads hexadecimal pairs into a file

There are no flags, as these are supposed to be extremely simple.

## hexin

If it happens that you provide an odd number of characters for this program, the
last character will be seen as the least significant half of the byte:

	$ hexin example.dat <<< "aabbf"
	$ hexout example.dat
	AABB0F
