        ��  ��                  �       �� ��                                        % s   n0  F T P   ��p��� F T P   ����h���x�����  % s   /   % s " < A   H R E F = " . . " > ���d\
Nn0����h���x�����x0< / A > < B R >     �       �� ��                                ����h���x�����         & l t ; i"}& g t ;  T e m p o r a r y   I n t e r n e t   F i l e s  C o o k i e s  H i s t o r y                 �       �� ��                             1 zvL��o0S0n0q�r�����x0n0q�x�~�}��06RP�W0f0D0�0_0�0h�:yg0M0~0[0�00�Nn0q�r������0x��bW0f0O0`0U0D00                  R       �� ��                               
 u�p�������r������x�� r�����p���o���k0�c�}W0~0Y0K0?               �      �� ���                               5 S0n0  W e b   q�������}�o0��d0K0�0~0[0�00{0h0�0i0n0  W e b   q�������}�o0  h t t p : / /   g0�Y~0�0~0Y00- S0n0  W e b   q�������}�o0��d0K0�0~0[0�00  q�������}��0�xK0�0f0K0�00�0�0�vW0f0O0`0U0D00, S0n0  W e b   q�������}�o0����|����0�rKaK00�s(W)R(ug0M0~0[0�00�_g0�0�0�vW0f0O0`0U0D00' S0n0q�r�����n0~�w�m�����h�o0�x��g0M0~0[0�00  �Nn0q�r������0x��bW0f0O0`0U0D00 O K  w�l���~���    P      �� ��                  �.  �.  X   �.  /     /  /  �  J/  J/  h
  N/  P/  �
  b/  j/  (  v/  �/  �     INTERNET_ERROR_BASE
   0   No more Internet handles can be allocated
     The operation timed out
   0   The server returned extended information
  D   An internal error occurred in the Windows Internet extensions
    The URL is invalid
    4   The URL does not use a recognized protocol
    8   The server name or address could not be resolved
  @   A protocol with the required capabilities was not found
      The option is invalid
 4   The length is incorrect for the option type
   (   The option value cannot be set
    <   Windows Internet Extension support has been shut down
 $   The user name was not allowed
 $   The password was not allowed
  $   The login request was denied
  (   The operation has been cancelled
  H   The supplied handle is the wrong type for the requested operation
 D   The handle is in the wrong state for the requested operation
  4   The request cannot be made on a Proxy session
 ,   The registry value could not be found
 ,   The registry parameter is incorrect
   0   Direct Internet access is not available
   $   No context value was supplied
 (   No status callback was supplied
   (   There are outstanding requests
    ,   The information format is incorrect
   ,   The requested item could not be found
 <   A connection with the server could not be established
 @   The connection with the server was terminated abnormally
  0   The connection with the server was reset
  $   The action must be retried
    $   The proxy request is invalid
  @   User interaction is required to complete the operation
        The handle already exists
 <   The date in the certificate is invalid or has expired
 D   The host name in the certificate is invalid or does not match
 L   A redirect request will change a non-secure to a secure connection
    L   A redirect request will change a secure to a non-secure connection
    0   Mixed secure and non-secure connections
   $   Changing to non-secure post
   8   Data is being posted on a non-secure connection
   D   A certificate is required to complete client authentication
   8   The certificate authority is invalid or incorrect
 @   Client authentication has not been correctly installed
    X   An error has occurred in a Wininet asynchronous thread. You may need to restart
   D   The protocol scheme has changed during a redirect operaiton
   ,   There are operations awaiting retry
   $   The operation must be retried
 (   There are no new cache containers
 D   A security zone check indicates the operation must be retried
 ,   The requested operation is invalid
    D   There is already an FTP request in progress on this session
   (   The FTP session was terminated
    (   FTP Passive mode is not available
 (   A gopher protocol error occurred
  (   The locator must be for a file
    4   An error was detected while parsing the data
     There is no more data
     The locator is invalid
    8   The locator type is incorrect for this operation
  0   The request must be for a gopher+ item
    ,   The requested attribute was not found
 ,   The locator type is not recognized
    ,   The requested header was not found
    @   The server does not support the requested protocol level
  @   The server returned an invalid or unrecognized response
   ,   The supplied HTTP header is invalid
   0   The request for a HTTP header is invalid
  (   The HTTP header already exists
    (   The HTTP redirect request failed
  8   An error occurred in the secure channel support
   4   The file could not be written to the cache
    4   The TCP/IP protocol is not installed properly
 ,   The HTTP request was not redirected
   @   A cookie from the server must be confirmed by the user
    <   A cookie from the server has been declined acceptance
 4   The computer is disconnected from the network
     The server is unreachable
 (   The proxy server is unreachable
   8   The proxy auto-configuration script is in error
   D   Could not download the proxy auto-configuration script file
   @   The HTTP redirect request must be confirmed by the user
   ,   The supplied certificate is invalid
   0   The supplied certificate has been revoked
 t   The Dialup failed because file sharing was turned on and a failure was requested if security check was needed
 1  0   �� B A S I C . D L G                 <HTML STYLE="color: #E7CE4A; font-family: MS Gothic; font-size: 18; width:400px; height:215px">

<!--
 ********************************************************************
 * Copyright (c) 1999 Microsoft Corporation
 *
 * basic.dlg
 *
 * Description
 *   HTML page for wininet replaceable UI - basic authentication dialog. 
 *
 * Dialog parameters
 *   string with embedded nulls of the form
 *     ok_caption\0cancel_caption\0default_username\0default_password
 *   ok_caption         not used
 *   cancel_caption     not used
 *   default_username   initially fill in edit box with this default 
 *                      user name
 *   default_password   initially fill in edit box with this default
 *                      password
 *
 * Dialog returns
 *   on user canceling dialog
 *     0
 *   on user OKing dialog
 *     string with embedded nulls of the form
 *       OK\0username\0password
 *     OK               the literal string "OK"
 *     username         the username entered by the user
 *     password         the password entered by the user
 ********************************************************************
-->

<HEAD>

<meta http-equiv="Content-Type" content="text/html; charset=shift_jis">

<SCRIPT LANGUAGE="JavaScript" defer>

  window.onerror = HandleError

  function HandleError(message, url, line)
  {
    /* To debug, uncomment this
    var L_Dialog_ErrorMessage = "An error has occured in this dialog.";
    var L_ErrorNumber_Text = "Error: ";

    var str = L_Dialog_ErrorMessage + "\n\n" 
        + L_ErrorNumber_Text + line + "\n"
        + message;

    alert (str);
    */

    return true;
  }

  function OnDialogLoad()
  {
    // get the arguments
    arrArgs = window.dialogArguments.split("\0");

    // set the default return value
    window.returnValue = 0;

    username.onkeydown = new Function("CheckForReturnKeyInUsername()");
    password.onkeydown = new Function("CheckForReturnKeyInPassword()");

    username.value = arrArgs[2];
    password.value = arrArgs[3];
  }

  function CheckForReturnKeyInUsername()
  {
    if (window.event.keyCode == 13) 
    {
      password.focus();
    }
  }

  function CheckForReturnKeyInPassword()
  {
    if (window.event.keyCode == 13) 
    {
      btn1.focus();
    }
  }

  function OnOK()
  {
    var result="OK\\0"+username.value+"\\0"+password.value;
    window.returnValue=result;
    window.close();
  }

</SCRIPT>

</HEAD>

<BODY BGCOLOR="#424242" SCROLL=No STYLE="margin-left:0px;margin-top:0px;margin-right:0px;margin-bottom:0px;" onLoad="OnDialogLoad()">

  <STYLE>
    H1 { color: #424242; font-size: 1; }
    .btn {font: bold; font-family:MS Gothic; font-size:12pt; color:black; text-align:center }
  </STYLE>

  <DIV STYLE="position:absolute; top:0; left:0; width=100%; height=100%;">
    <TABLE Width=100% Height=100% Border=0 cellSpacing=0 cellPadding=0>
      <TR>
        <TD Width=16px Height=16px background="PanelNE.gif"></TD>
        <TD Height=16px background="PanelN.gif"></TD>
        <TD Width=16px Height=16px background="PanelNW.gif"></TD>
      </TR>
      <TR>
        <TD Width=16px background="PanelE.gif" ></TD>
        <TD><H1>SP</H1></TD>
        <TD Width=16px background="PanelW.gif" ></TD>
      </TR>
      <TR>
        <TD Width=16px Height=16px background="PanelSE.gif"></TD>
        <TD Height=16px background="PanelS.gif"></TD>
        <TD Width=16px Height=16px background="PanelSW.gif"></TD>
      </TR>
    </TABLE>
  </DIV>

  <DIV STYLE="position:absolute; left: 20; top:20; width:360;">հ�ް�����߽ܰ�ނ���͂��Ă��������B</DIV>

  <DIV id="DialogText" STYLE="position:absolute; left:20; top=64; width=360">
    <table cellspacing=0>
      <tr>
        <td align=right>հ�ް��:&nbsp;</td>
        <td><INPUT id=username type=text width=20 STYLE="border-color:#969696; background-color:#161616; font-family: MS Gothic; font-size: 18; color:#10d710;" onfocus="focus()"></td>
      </tr>
      <tr>
        <td align=right>�߽ܰ��:&nbsp;</td>  
        <td><INPUT id=password type=password width=20 STYLE="border-color:#969696; background-color:#161616; font-family: MS Gothic; font-size: 18; color:#10d710;" onfocus="focus()"></td>
      </tr>
    </table>
  </DIV>

  <HR ID=DividerTop NOSHADE STYLE="position:absolute; left:20; top:151; width:360; height:2; color:#323232;">
  <HR ID=DividerBtm NOSHADE STYLE="position:absolute; left:20; top:153; width:360; height:2; color:#808080;">

  <DIV STYLE="position:absolute; left: 20; top:158;">
    <TABLE width=100%>
      <TD id=buttons align=left>
        <INPUT TYPE=Button id=btn1 VALUE="OK" CLASS=btn onClick="OnOK()">&nbsp;
        <INPUT TYPE=Button id=btn2 VALUE="��ݾ�" CLASS=btn onClick="window.close()">&nbsp;
      </TD>
    </TABLE>
  </DIV>

</BODY>

</HTML>
   �  <   �� E X C L A M A T I O N . G I F                 GIF89aA : �     �� ��٪!! ��;1��&��z������"��%TL3������^[P��!������$�u3			��}^�� ..-$$#���EEC����ttt��"����
��((%��!;94�� �Are8��


                  !�  1 ,    A :  ���pH,����!�^ȨtJ5FB����V���I��?-�7�f�B����h�~����t - 6-{�Qceh/��"6��Dpf u"�"y�z�g\"����X�t3���"22��_'Xe ���"#7��ao'�ȹv���`}']ת#��$�Tc� ��#�ͱ�Q!!��\��`�s����䊜:��3h���,hxƐ��b ��b0��A2Z�a�0~æ���B"E�XtX)����2f��щQ,��Ń=iظ��a��8jr
	.<�S��1*"�у.\��4 .�l��#;b�f0�:1T�*<�`���+V���&�>�J�0FŌY�Pa 2�9�v����H�&�e��8���oh���e�a���bB��k�V�S79,@;����_U����F�ѣ)�}��o0Lv	|�5�ʕ4_`A�86l�aCm�1t��E(|�O=��x8�@,���~��V	`��b�`�E�T#̧B��H� ��A7�FL���u��=R�`�r$�X� � *n B"��r�D�(
�uC��� @$ ��AUl �]yV]t���4耏L� YdZ��� ؁e�	*\���	��
 @	+���~�AK�4P��.��� ��� <𠏉
�@4�e���Ξ}uf �p�S�0���N�h��`���Y���ne欵�j����+���
hI䊽��Oz�����y���h m���z-%�����k�\P�X&�[�,��P0m��b�'��(~`"!�+�;��*�P��p��	g 20�0���'t���A���݂�uP^rRk��"g ��%�0�9Dj$P:B9����9�~<�s�
�����"�.��+#����O�u��]Ym�f���)d`��n`�Gz�c��i{�����
7�=�Lw

h��/���@���<s�$v`���`���lz
�+�~#��苹����H� w���#޳�+и�D�I�4 ��u5K��>޽��!�|��׉�/B�!�J���|^��vIz���������p�CC�#�� S�b�9���ݖ|7�ӡ.u�k�p�(Ll�$ �=�J?��>'7���	Lఈ� L AF.���\j�;�Jv��ypq����H�{h�gA�a0N�^q�C���h�VX ��kp��V�����N�քp�?�`hmg>$j1n6l����Óm���H� . d ��B�L�"���  xP	@��ؠ'����x���P蓟���FIJRn�Q�rؑH ��$2��My����	��<�.w��T>��Bp���� 7���s���f:��|~��"!=���1�r̩x���8�INO5rH9 ����2}���<��t�A  ; v   4   �� P A N E L E . G I F                   GIF87a  �  111999BBBRRRZZZccckkk{{{������������������������,       +�c�8kI��W]`&z%v�險���1��l���堞7�� ;  s   4   �� P A N E L N . G I F                   GIF87a  �  )))BBBJJJcccsss{{{������                        ,       (p�I�(8�I��'�Di�(a���p,tm�x��|����p��  ; �  4   �� P A N E L N E . G I F                 GIF87a  �     			


   !!!"""###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[\\\]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������,       s �H���=�I�p��=�"�g�Ŋ�<DT��ŏ 5�YTg��5cR�L�P�1�Ȝ)�a�5���s�C8&�����gP�D�������c�6���ԩF�N�
�jӬ^���*$  ;  �   4   �� P A N E L N W . G I F                 GIF87a  �     !!!)))111999BBBJJJRRRZZZcccsss{{{���,       L��I�R��{��b8i�_�$�����FU]�A'|��:bH$&r:���D��&�Px*��*;�Z�X�+�����C" ; t   4   �� P A N E L S . G I F                   GIF87a  �  ���BBB111)))                            ,       )0�I��8�ͻ� &�di
C���@�p,Em�xMt��P5+�" ;�  4   �� P A N E L S E . G I F                 GIF87a  �     			


   !!!"""###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[\\\]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������,       h �쁳f�!*HРB<1�D�^��qcF�'~�cǒR�|8���0c�di�E��8sj��E�@�
U2Fe�!�*E)RI�B���jN�X�b ; �   4   �� P A N E L S W . G I F                 GIF87a  �  ���BBB;::333111)))!!!                   ,       H0�IIA��,>7y��ݕ�	�)���Koi� ��pXP���dр1���YRɮX'��r���r����p ; z   4   �� P A N E L W . G I F                   GIF87a  �  ���BBB111)))                            ,       /0�I�(X�,&7y�8^hJd�������v����M�m��"�#�  ;  �	  8   �� Q U E S T I O N . G I F                   GIF89aA : �� ���
## 11-((%00-GGC%%#FFC//-EEC$$#!! ..-uus.-#(' 
*)#3./+KF,52#41#+*%32-HGB��#��!��$��$��"��%��%��&ӯ ӯ!�����{�mcTTH&#%"!-+#��z75-%$ ('#21-����������������������������������������� �� ����!��!��"��"��"�� ��#Ӯ �������i�z�{�lr^cRTFTH��0��1�2�}2B9�z3�y3�w3�u3�r53-re8`V1]T2YQ3# D?,62#51#,*#64-^[P=;4��������������������������������Ӥ�����������۬ګ٪ӥ�������������������ޯݯ������������Ҧө���w�ws\�ir]cPcQTETEL?B83,60TL3>:-0-#���a����_~^}^���n
�k
�tTDE9?4;1p`1ue8%!%!
(& +)#_[P<:4'&#�^^
;94
&$ )'#&%#0/-
���ttt


			   !�    ,    A : @� H���� �̛�G��q#J�HQ�<�*L����
MBƫWbœ�ɳ0�YR�8a�	-8qVy�,�t�Q@I4�E	���BK���J�:�W!Biӷo�E^�� `&�jɂ�
�*U�H��	�!DrQE���#F�%J���?�왜���8
�"hj�.�)O�$)R�#D�tM5d(Ѣ��	Z�Z��b���3ܯ�P�:N�*牖��3'�U��N�!=�kj ֭]�.F}����5�����(D��w��˻��������˟�^?��M�6����h��	L@�=`���A\�;����G�E
4�A�T� QGA��0s�dB9m�SNo�Ć5�sO>�}X�J�hDA�ha�Tq�EeS�u-S���!���Om�%�Qe�#GNl]�S8�J'�4�HsS��_���� ��	?�!����5���0�E��	�VBp�k�Iݚ�I7�u�8�O?%	���sO4Ʉ�L��r�駛��8�"#����������?5��(P�!�Q	г���ʣ�M &�1�f�Ϯ�5�<H9 �v���dk)��V�`7��T��¹i���6�` =�$�-B�u��{H�E
5���T,S�5(�=��+г$��6m�K
1P5U5cpi��h�>���Ҫ���U.�V�fP)�<?��vۂ����8��\D	G���Tb��#����ae`<��֐Z^�e���%�PCU/��	X"�	�m����Ee���{jIEpJ��-�"�43.�,��ij"*�1���?�4ϯDF�!\덙�B �H��	2�j�!*���T7L2��AAGQ@Ou�B�e�W�*�,B�T���:u�_�������uR��
a�q���v�%�:��`��0o�<�U�z���\�s?�8�v����v��������U��1�	�LaR�U�nu�x�
�a���0`�j��O"�[M�)�L<2����)�@�V r(r%<����+\A
⠎�p�	�!���э��w�VZ����c �ҕ���X�
d2���'I@0����
��/�5�_���p�� `��F������@H�hOU��xAm�g0��	C��`�b&$�B	^ �4xRd�6�����ؙ$���c�:�b1���
J������;�R`x���T����1Ё*gB'�p��f�⇎�xLØi�J����,M*�@��j�$~��'aX #���`pA�ZT�$&,a�Hra��*{D��M�ek���� �% m���,��F�0��Y$)B��M-li.�$�%�xE/�V
�%0ʈF�B��A�=ZK��"QW�"��+�V��vTM�0�1Xǿ(�����G4�T��a&	���#�
����H��Xs��Q�0���D|հ� CkC�Rf8#�ޅf*�(��e�No��;°;E�ZyӜ��0
J,�(TTAӤ&tҩ�A���1L<V��d9'�I�m5�H�lS��BڀNx�R�&@�8�4���&t�W�
a���������x��? ')�ZNUx�W�k�N(gP�p�T��q�{:5�}� �&��˝�[���u���y�g��� ��;�a�Foz��(`�WX���ء*��Q�H`���x�����^Y>�����Q�K��燿���Vu��Hb��'}�q>������@rW���'M� �Ǌ���&;���0 A ;   