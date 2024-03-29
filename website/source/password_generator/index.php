<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <title>Shasta Exchange</title>
    <style type="text/css">
        <style type="text/css">
       .about_the_company {
     border-radius: 10px;
     background: #008CBA;
     border: 3px solid #000000;
     margin: 0 0.5em 0.5em 0.5em;
     font-size: 3.5em;
     color: #ffffff;
     padding: 1em;
    }
    </style>
  
    
    <link rel="stylesheet" href="/include_stylesheet.css"/>
    
		<script>
		 var sha256 = function sha256(ascii) {
	function rightRotate(value, amount) {
		return (value>>>amount) | (value<<(32 - amount));
	};
	
	var mathPow = Math.pow;
	var maxWord = mathPow(2, 32);
	var lengthProperty = 'length'
	var i, j; // Used as a counter across the whole file
	var result = ''

	var words = [];
	var asciiBitLength = ascii[lengthProperty]*8;
	
	//* caching results is optional - remove/add slash from front of this line to toggle
	// Initial hash value: first 32 bits of the fractional parts of the square roots of the first 8 primes
	// (we actually calculate the first 64, but extra values are just ignored)
	var hash = sha256.h = sha256.h || [];
	// Round constants: first 32 bits of the fractional parts of the cube roots of the first 64 primes
	var k = sha256.k = sha256.k || [];
	var primeCounter = k[lengthProperty];
	/*/
	var hash = [], k = [];
	var primeCounter = 0;
	//*/

	var isComposite = {};
	for (var candidate = 2; primeCounter < 64; candidate++) {
		if (!isComposite[candidate]) {
			for (i = 0; i < 313; i += candidate) {
				isComposite[i] = candidate;
			}
			hash[primeCounter] = (mathPow(candidate, .5)*maxWord)|0;
			k[primeCounter++] = (mathPow(candidate, 1/3)*maxWord)|0;
		}
	}
	
	ascii += '\x80' // Append Ƈ' bit (plus zero padding)
	while (ascii[lengthProperty]%64 - 56) ascii += '\x00' // More zero padding
	for (i = 0; i < ascii[lengthProperty]; i++) {
		j = ascii.charCodeAt(i);
		if (j>>8) return; // ASCII check: only accept characters in range 0-255
		words[i>>2] |= j << ((3 - i)%4)*8;
	}
	words[words[lengthProperty]] = ((asciiBitLength/maxWord)|0);
	words[words[lengthProperty]] = (asciiBitLength)
	
	// process each chunk
	for (j = 0; j < words[lengthProperty];) {
		var w = words.slice(j, j += 16); // The message is expanded into 64 words as part of the iteration
		var oldHash = hash;
		// This is now the undefinedworking hash", often labelled as variables a...g
		// (we have to truncate as well, otherwise extra entries at the end accumulate
		hash = hash.slice(0, 8);
		
		for (i = 0; i < 64; i++) {
			var i2 = i + j;
			// Expand the message into 64 words
			// Used below if 
			var w15 = w[i - 15], w2 = w[i - 2];

			// Iterate
			var a = hash[0], e = hash[4];
			var temp1 = hash[7]
				+ (rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25)) // S1
				+ ((e&hash[5])^((~e)&hash[6])) // ch
				+ k[i]
				// Expand the message schedule if needed
				+ (w[i] = (i < 16) ? w[i] : (
						w[i - 16]
						+ (rightRotate(w15, 7) ^ rightRotate(w15, 18) ^ (w15>>>3)) // s0
						+ w[i - 7]
						+ (rightRotate(w2, 17) ^ rightRotate(w2, 19) ^ (w2>>>10)) // s1
					)|0
				);
			// This is only used once, so *could* be moved below, but it only saves 4 bytes and makes things unreadble
			var temp2 = (rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22)) // S0
				+ ((a&hash[1])^(a&hash[2])^(hash[1]&hash[2])); // maj
			
			hash = [(temp1 + temp2)|0].concat(hash); // We don't bother trimming off the extra ones, they're harmless as long as we're truncating when we do the slice()
			hash[4] = (hash[4] + temp1)|0;
		}
		
		for (i = 0; i < 8; i++) {
			hash[i] = (hash[i] + oldHash[i])|0;
		}
	}
	
	for (i = 0; i < 8; i++) {
		for (j = 3; j + 1; j--) {
			var b = (hash[i]>>(j*8))&255;
			result += ((b < 16) ? 0 : '') + b.toString(16);
		}
	}
	return result;
};
function compute()
{
	
  var rounds = document.getElementById("password_hash_multiplier").value; //a number you won't forget that is not your known favorite number within a range of 10 and 1,000,000
	var index = 0;
	var input = document.getElementById("password_input_one").value;
	var last_result = input;
	while(index <=	rounds)
	{
		last_result = last_result + input;
		
		index = index + 1;
	
	}
	if(rounds > 5000){ rounds = 5000;}
	index = 0;
	while(index <= rounds)
	{
		last_result = sha256(last_result);
		
		index = index + 1;
	}
	
	document.getElementById("password_result").innerHTML = sha256(last_result);
}
  </script>
  </head>
  <body>
    <div id="logo_business_name">
      <h1 id="business_name">Shasta Exchange</h1>
      <h2 id="business_elevator_pitch">Digital based printed media</h2>
    </div>
    
     <?php include('/usr/local/apache2/htdocs/include_header_flag.php'); ?>
    <?php include('./../include_navigation.php'); ?>
    <?php include('/usr/local/apache2/htdocs/software/include_secondary_navigation.php'); ?>
    <div style="margin: 3em;">&nbsp;</div>
    <div class="menu_header">
     Password Generation Form
    </div>
    <div class="blog_introduction">
    &nbsp;&nbsp;&nbsp;&nbsp;Input a password that you will remember, then select a number you will also remember. The password generator will create a line of text that is your password repeating as many times as the number you inputted.
    <br/><br/>
    The time to compute is depednant upon a higher number, although in theory anything under one milliom should not take longer than five seconds.
    <br/><br/>
    larger numbers may take slightly longer to compute and is used to concat your input pass phrase that many times as a defense against rainbow tables(customer data leaks may not affect you in most cases due to this large and randomized salt).  <br/><br/>
    <hr/><br/><br/>
    
    <form action="javascript:preventDefault();">
    <h3>A memorable pass phrase</h3>
     <input id="password_input_one"  type="password" style="height:2em;font-size:100%;" />
    
     <br/><br/>
        <h3>pick and remember this number between one hundred and one million</h3>
       
     <textarea id="password_hash_multiplier"  style="font-size:100%;">100</textarea>
     <a href="javascript: void();" onMouseUp="compute();">Generate Reproduceable Passphrase</a>
    </form> 
    <div id="password_result">Your password will appear here</div>
    </div>
    
     <div style="margin: 3em;">&nbsp;</div>
    <div class="menu_header">
     Pseudo Code
    </div>
    <div class="blog_introduction" style="font-family: 'Courier New', monospace; font-size:1em;">
    let index = 0;<br/>
    let combined_string ="";<br/>
    while(index < large_number_to_memorize)<br/>
    {<br/>
    	combined_string = combined_string + combined_string;
    <br/>
    }<br/>
    if(rounds > 5000){ rounds = 5000;}<br/>
    index = 0;<br/>
    while(index <= rounds)<br/>
    {<br/>
	combined_string  = sha256(combined_string );<br/>
	index = index + 1;<br/>
}<br/>
    
    </div>
    
      <div style="margin: 3em;">&nbsp;</div>
    <div class="menu_header">
     How this helps you.
    </div>
    <div class="blog_introduction">
    &nbsp;&nbsp;&nbsp;&nbsp;This software is capable of being retrieved online and is executed on your computer hardware using the JavaScript language, contained within the confines of your web browser and thus incapable of producing longterm and shortterm damages to your device. This method of delivery is nessecary due to it being crucial for password generation to occur only the user' device
    <br/><br/>
    Password generation occurs by computing a result derived from a sha256 program, however inheritly this is not safe due to the invention of rainbow tables and bruteforcing; A password generated from one run of sha256 can be quickly searched through a precomputed database of all possibilities or likely possibilities.
       <br/><br/>
       The first solution to deflect rainbowtables and bruteforcenis to understand that there is a threshhold of efficacy; That is to say most people generating a rainbow table will have to confront that most people dont want to buy a rainbow table that is greater than 50gigabytes to download which is usually a database of every sha256 result from a password guess of one character length to about seven character lengths. To be clear anything longer then eight characters becomes a database that grows exponentially per additional guessable character length. 
         <br/><br/>
       Thus a long password is the solution, however humans want to remember short passwords so the solutiom is to memorize a short password and a number, this number will repeat your password as many-times as the number you inputted(and memorized), and then that long password is ran through the sha256 program that many times(up to 5000 times). This produces a reproduceable password that is 64 characters, so now you get to keep your input password(such as your childs birthday) safe(in most cases throughout your life) <i>and</i> your password that you give your company and or website that is sixty four characters long will also be unguessable through guessing randomly at a rate of one guess per three seconds.
    </div>
    
 
    <div style="margin:3em;"></div> 
    <div style="margin:0.5em;text-align:center; color:#ffffff; font-size:2.5em;">Page created by Shane Bryan Betz</div>
    <div style="margin:6em;"></div>
   </body>
	 </html>