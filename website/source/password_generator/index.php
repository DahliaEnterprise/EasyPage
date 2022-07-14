<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <title>Shasta Exchange</title>
    <style type="text/css">
    * {
      margin: 0px 0px 0px 0px;
      padding: 0px 0px 0px 0px;
    }

    body {
     background-color: #3D6198;
    }

    #business_name {
      font-size: 5.11em;
      text-align: center;
      padding: 0.5em 0.5em 0 0.5em;
      margin: 0em 0.5em 0 0.5em;
      font-family: PlayFairFont;
      text-shadow: 0 0 2px #000000, 0 0 2px #000000, 0 0 5px #000000, 0 0 10px #000000; 0 0 10px #000000; 0 0 10px #000000;
      color: #f64f4f;
    }
  
   
    div.header_quick_links {
      text-align: center;
      width: 99.999999%;
      padding-top: 2.5em;
      padding-bottom: 2.5em
    }

    #business_elevator_pitch {
      font-size: 2.4em;
      text-align: center;
      font-family: PlayFairFont;
      padding: 0 0.5em 0.5em 0.5em;
      margin: 0.5em 0.5em 0.5em 0.5em;
      text-shadow: 0 0 2px #7d1e3e, 0 0 2px #7d1e3e, 0 0 3px #7d1e3e, 0 0 5px #000000, 0 0 5px #000000; 0 0 5px #000000;
      color: #f64f4f;
      font-weight: 900;
    }

    #logo_business_name {
     width: 99.999999%;
     background: url("/demo_background.jpeg");
     background-repeat: no-repeat;
     background-position: center 120px;
     padding-bottom: 200px;
     border-bottom: 3px solid #f64f4f;
    }

    @font-face {
     font-family: PlayFairFont;
     src: url("/externally_provided/fonts/PlayFair_Display/PlayfairDisplaySC-Regular.otf");
    }

    @font-face {
     font-family: MochiPopOne;
     src: url("/externally_provided/fonts/mochiypop/fonts/ttf/MochiyPopOne-Regular.tff");
    }

    .easy_page_header {
     text-align: center;
     
     padding: 1em;
     margin: 0 2em 1em 2em;
     border-radius: 10px;	
     background: #008CBA;
     box-shadow: 3px 3px 5px #000000;
    }

    a.shasta_exchange_navigation:link {
    color:#ffffff;
     text-align: center;
     font-size: 3.5em;
     text-decoration: none;
     
    }

    a.shasta_exchange_navigation:visited {
     font-family: MochiPopOne;
     color: #ffffff;
     text-shadow: 0 0 2px #7d1e3e, 0 0 2px #7d1e3e, 0 0 3px #7d1e3e;
     text-decoration: none;
    }

    .menu_header {
     text-align: center;
     font-size: 3.5em;
     font-family: PlayFairFont;
     text-shadow: 0 0 2px #7d1e3e, 0 0 2px #7d1e3e, 0 0 3px #7d1e3e;
      color: #f64f4f;
      font-weight: 900;
    }
	
    .blog_introduction {
     border-radius: 10px;
     background: #008CBA;
     border: 3px solid #000000;
     margin: 0 0.5em 0.5em 0.5em;
     font-size: 3.5em;
     color: #ffffff;
     padding: 1em;
    }
    </style>
  </head>
  <body>
    <div id="logo_business_name">
      <h1 id="business_name">Shasta Exchange</h1>
      <h2 id="business_elevator_pitch">Digital based printed media</h2>
    </div>
    
   
    <?php include('./../include_navigation.php'); ?>
    <div style="margin: 3em;">&nbsp;</div>
    <div class="menu_header">
     Repeat input X times, then hash 5000 times.
    </div>
    <div class="blog_introduction">
    &nbsp;&nbsp;&nbsp;&nbsp;Input a password that you will remember, then select a number you will also remember. The password generator will create a line of text that is your password repeating as many times as the number you inputted, it will then take this lengthy line of text and input it automatically into what is called a "hash" program; A hash program has many uses, this particular use is to produce a reproduceable randomized password based on your predictable password.
    This hash program uses Javascript and does not have any actions of sending any data to Shasta Exchange. All data is on the ram memory of your current device(or more preceisly the device accessing this), the only way your input password will leak is if you keep this page open with your data not yet cleared.
    <br/><br/>
    <hr/><br/><br/>
    
    <form action="javascript:preventDefault();">
    <h3>A memorable pass phrase</h3>
     <textarea id="password_input_one"  style="height:2em;font-size:100%;">
     </textarea>
     <br/><br/>
        <h3>pick and remember this number between one hundred and one million</h3>
        <div>larger numbers may take slightly longer to compute and is used to concat your input pass phrase that many times as a defense against rainbow tables(customer data leaks may not affect you in most cases due to this large and randomized salt).
     <textarea id="password_hash_multiplier_one"  style="font-size:100%;">
     100
     </textarea>
     
    </form> 
    
    </div>
    
    
 
    <div style="margin:3em;"></div> 
    <div style="margin:0.5em;text-align:center; color:#ffffff; font-size:2.5em;">Page created by Shane Bryan Betz</div>
    <div style="margin:6em;"></div>
   </body>
  </html>
