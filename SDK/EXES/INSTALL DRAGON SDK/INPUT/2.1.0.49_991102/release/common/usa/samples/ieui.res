        ��  ��                  �      �� ���     0 	        (   8            �  �  �                �  �   �� �   � � ��  ��� ��� �ʦ   @   `   �   �   �   �  @   @   @@  @`  @�  @�  @�  @�  `   `   `@  ``  `�  `�  `�  `�  �   �   �@  �`  ��  ��  ��  ��  �   �   �@  �`  ��  ��  ��  ��  �   �   �@  �`  ��  ��  ��  ��  �   �   �@  �`  ��  �  ��  �� @   @   @ @ @ ` @ � @ � @ � @ � @   @   @ @ @ ` @ � @ � @ � @ � @@  @@  @@@ @@` @@� @@� @@� @@� @`  @`  @`@ @`` @`� @`� @`� @`� @�  @�  @�@ @�` @�� @�� @�� @�� @�  @�  @�@ @�` @�� @�� @�� @�� @�  @�  @�@ @�` @�� @�� @�� @�� @�  @�  @�@ @�` @�� @� @�� @�� �   �   � @ � ` � � � � � � � � �   �   � @ � ` � � � � � � � � �@  �@  �@@ �@` �@� �@� �@� �@� �`  �`  �`@ �`` �`� �`� �`� �`� ��  ��  ��@ ��` ��� ��� ��� ��� ��  ��  ��@ ��` ��� ��� ��� ��� ��  ��  ��@ ��` ��� ��� ��� ��� ��  ��  ��@ ��` ��� �� ��� ��� �   �   � @ � ` � � � � � � � � �   �   � @ � ` � � � � � � � � �@  �@  �@@ �@` �@� �@� �@� �@� �`  �`  �`@ �`` �`� �`� �`� �`� ��  ��  ��@ ��` ��� ��� ��� ��� ��  ��  ��@ ��` ��� ��� ��� ��� ��  ��  ��@ ��` ��� ��� ��� ��� ���   �  �   �� �   � � ��  ��� ����������������������������������������������������������         �����         �����         �����         �����........  ����VLLLLLLL  ������������  ����91111111  ����77777777.  ���NNNNNNNNL  ������������  ���999999991  ��77777. ���NNN����NNL ��	���				��� ��z999zzzz991 ��77���7. ���NN������NL ��	��	���	��� ��z99z���zz91 ��7. ����7. ���NL �����NL ��	�� ����	�� ��z91 ����z91 ��7. ����7. ���NL �����NL ��	�� ����	�� ��z91 ����z91 ��7. ����7. ���NL �����NL ��	�� ����	�� ��z91 ����z91 ��7. ����7. ���NL �����NL ��	�� ����	�� ��z91 ����z91 ��77.   77. ���NNL   N�NL ��	���   �	�� ��z991   9z91 ��777....77. ���NNNLLLLNNL ��	���������� ��zz991111991 ���77777777. ����NNNNNNNNV ���	��������� ���z999999999 �������������������������							�������zzzzzzz��������������������������������������������������������������������������������������������������������������������"  4   �� P R O M P T . D L G         0 	        <HTML style="color:#E7CE4A; font-family:Arial; font-size:18; width:400px; height:215px">

<!--
 ********************************************************************
 * Copyright (c) 1999 Microsoft Corporation
 *
 * prompt.dlg
 *
 * Description
 *   HTML page for ieui replaceable UI - javascript prompt box. 
 *
 * Dialog parameters
 *   string with embedded nulls of the form
 *     message_text\0default_response
 *   message_text       text to display as prompt in dialog
 *   default_response   initially fill in edit box with this default
 *                      text
 *
 * Dialog returns
 *   on user canceling dialog
 *     null
 *   on user selecting OK
 *     string of the text user entered into edit box (if no text is
 *     entered, a blank string "" is returned -- not null)
 ********************************************************************
-->

<HEAD>

  <META http-equiv="Content-Type" content="text/html; charset=iso-8859-1">

  <TITLE id=dialogTitle>JavaScript Prompt</TITLE>

  <SCRIPT LANGUAGE="JavaScript" defer>

    function OnDialogLoad()
    {
      // get the arguments
      var arrArgs = new Array();
      arrArgs = window.dialogArguments.split("\0");

      if (arrArgs.length >= 2)
      {
          PromptMessage.innerText = arrArgs[0];
          userInput.value = arrArgs[1];
      }
        
      userInput.onkeydown = new Function("CheckForReturnKey()");
      userInput.focus();
      MoveEditCursorToEnd();

      // set the default return value
      window.external.returnValue = null;
    }

    function CheckForReturnKey()
    {
      if (window.event.keyCode == 13) 
      {
        OnOK();
      }
    }

    function MoveEditCursorToEnd()
    {
      tr = userInput.createTextRange();
      tr.moveStart("textedit", 1);
      tr.moveEnd("textedit", 1);
      tr.select();
    }

    function OnOK()
    {
      window.external.returnValue = userInput.value;
      window.external.close();
    }

    function OnCancel()
    {
      window.external.close();
    }

  </SCRIPT>

</HEAD>

<BODY BGCOLOR="#424242" SCROLL=No STYLE="margin-left:0px;margin-top:0px;margin-right:0px;margin-bottom:0px;" onLoad="OnDialogLoad()">

  <STYLE>
    H1 { color: #424242; font-size: 1; }
    .btn {font: bold; font-family:Arial, san serif; font-size:12pt; color:black; text-align:center }
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

  <TEXTAREA id=PromptMessage tabindex=-1 readonly=1 STYLE="border:0; overflow:hidden; position:absolute; left:20; top:20; width:360px; height:86px; font-family:Arial; font-size:18; background-color:#424242; color: #E7CE4A;">
  </TEXTAREA>

  <INPUT TYPE=Text NAME="userInput" VALUE="" STYLE="border-color:#969696; position:absolute; left:20; top:113; width:360; font-family:Arial; font-size:18; background-color:#161616; color:#10d710;" onfocus="focus()">

  <HR ID=DividerTop NOSHADE STYLE="position:absolute; left:20; top:151; width:360; height:2; color:#323232;">
  <HR ID=DividerBtm NOSHADE STYLE="position:absolute; left:20; top:153; width:360; height:2; color:#808080;">

  <INPUT TYPE=Button VALUE="OK" CLASS=btn STYLE="position:absolute; left= 20; top=164;" onclick="OnOK()">
  <INPUT TYPE=Button VALUE="Cancel" CLASS=btn STYLE="position:absolute; left= 70; top=164;" onclick="OnCancel()">

</BODY>

</HTML>
  m  4   �� M S G B O X . D L G         0 	        <HTML STYLE="color: #E7CE4A; font-family: Arial; font-size: 18; width:400px; height:215px">

<!--
 ********************************************************************
 * Copyright (c) 1999 Microsoft Corporation
 *
 * msgbox.dlg
 *
 * Description
 *   HTML page for ieui replaceable UI - standard message box. 
 *
 * Dialog parameters
 *   string with embedded nulls of the form
 *     icon_gif_file\0message_text\0btn1_caption\0btn2_caption\0btn3_caption
 *   icon_gif_file      gif file in the DLL to use for icon
 *   message_text       text to display in body of message box
 *   btn1_caption       text of first button
 *   btn2_caption       text of second button (optional if only 1 btn)
 *   btn3_caption       text of third button (optional if only 1 or 2 btns)
 *
 * Dialog returns
 *   on user canceling dialog
 *     0
 *   on user selecting a button
 *     string of the text of the button selected
 ********************************************************************
-->

<HEAD>

<META http-equiv="Content-Type" content="text/html; charset=iso-8859-1">

<SCRIPT LANGUAGE="JavaScript">

  // Trap any possible scripting errors and ignore them...
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
    var arrArgs = window.dialogArguments.split("\0");

    Message.innerText = arrArgs[1];
    
    // set the default return value
    window.returnValue = 0;

    Icon.src = arrArgs[0];

    for (j=2,k=1;j<arrArgs.length;j++,k++) 
    {
      var text = arrArgs[j];
      if (text.length > 0)
      {
        eval("btn"+k+".value='"+text+"'");
        eval("btn"+k+".style.visibility='visible'");
      }
    }

    btn1.focus();
  }

  function BtnHandler()
  {
    var who=event.srcElement;
    window.returnValue=who.value;
    window.close();
  }

</SCRIPT>

</HEAD>

<BODY SCROLL=No STYLE="background-color:#424242; margin-left:0px; margin-top:0px; margin-right:0px; margin-bottom:0px;" onLoad="OnDialogLoad()">

  <STYLE>
    H1 { color: #424242; font-size: 1; }
    .btn {font: bold; font-family:Arial, san serif; font-size:12pt; color:black; text-align:center }
  </STYLE>

  <DIV STYLE="position:absolute; top:0; left:0; width=100%; height=100%;">
    <TABLE Width=100% Height=100% Border=0 cellSpacing=0 cellPadding=0>
      <TR>
        <TD Width=16px Height=16px background="PanelNE.gif"></TD>
        <TD Height=16px background="PanelN.gif"></TD>
        <TD Width=16px Height=16px background="PanelNW.gif"></TD>
      </TR>
      <TR>
        <TD Width=16px background="PanelE.gif"></TD>
        <TD><H1>SP</H1></TD>
        <TD Width=16px background="PanelW.gif"></TD>
      </TR>
      <TR>
        <TD Width=16px Height=16px background="PanelSE.gif"></TD>
        <TD Height=16px background="PanelS.gif"></TD>
        <TD Width=16px Height=16px background="PanelSW.gif"></TD>
      </TR>
    </TABLE>
  </DIV>

  <img id=Icon STYLE="position:absolute; left: 20; top:20;" src="" width="65" height="58">

  <TEXTAREA id=Message tabindex=-1 readonly=1 STYLE="border:0; overflow:hidden; position:absolute; left:95; top:20; width:285px; height:130px; font-family:Arial; font-size:18; background-color:#424242; color: #E7CE4A;">
  </TEXTAREA>

  <HR ID=DividerTop NOSHADE STYLE="position:absolute; left:20; top:151; width:360; height:2; color:#323232;">
  <HR ID=DividerBtm NOSHADE STYLE="position:absolute; left:20; top:153; width:360; height:2; color:#808080;">

  <DIV STYLE="position:absolute; left: 20; top:158;">
    <TABLE width=100% cellpadding=5>
      <TD id=buttons align=left>
        <INPUT TYPE=Button id=btn1 VALUE="blank" CLASS=btn STYLE="visibility:hidden;" onClick="BtnHandler()" tabindex=1>&nbsp;
        <INPUT TYPE=Button id=btn2 VALUE="blank" CLASS=btn STYLE="visibility:hidden;" onClick="BtnHandler()" tabindex=2>&nbsp;
        <INPUT TYPE=Button id=btn3 VALUE="blank" CLASS=btn STYLE="visibility:hidden;" onClick="BtnHandler()" tabindex=3>
      </TD>
    </TABLE>
  </DIV>

</BODY>

</HTML>
   &  4   �� W A R N I N G . G I F       0 	        GIF89a$ & �     h  �  �  �  �   h hh �h �h �h �h  � h� �� �� � ��  � h� �� �� �� ��  � h� �� �� �� ��  � h� �� �� �� ��   hh h� h� h� h� h hhhhh�hh�hh�hh�hh �hh�h��h��h�h��h �hh�h��h��h��h��h �hh�h��h��h��h��h �hh�h��h��h��h��h  �h �� �� �� �� � h�hh��h��h��h��h� ��h��������ᙙ��� ��h�������������� �hᙙ������� ��h��������������  �h �� �� �� �� � h�hh��h��h��h��h� ��h������������� ��h�������������� ��h�������������� ��h��������������  �h � �� �� �� � h�hh�h��h��h��h� ��h�ᙙ��������� ��h������������� ��h������������� ��h�������������  �h �� �� �� �� � h�hh��h��h��h��h� ��h������������� ��h�������������� ��h�������������� ��h��������������                                                                                                                        !�  � ,    $ & @� 	H����<0��� VXQH��C 1>�(��@�C�tq"BS�\�r�D�	Z �M�41"���Ǒ��<r䈜;�r4鳩ӧP]��ԋ+�T-��N��x�1�:��TdD��^j�W�r���y���V Lx0ت�):8p q܇4;��f`�r-K���(��P̥�tө]�~��lʍ�o��Y��j��G��|;ag�JcՋԨp�z!���{`���K�������^߮�;��/'�w ;  v   4   �� P A N E L E . G I F         0 	        GIF87a  �  111999BBBRRRZZZccckkk{{{������������������������,       +�c�8kI��W]`&z%v�險���1��l���堞7�� ;  s   4   �� P A N E L N . G I F         0 	        GIF87a  �  )))BBBJJJcccsss{{{������                        ,       (p�I�(8�I��'�Di�(a���p,tm�x��|����p��  ; �  4   �� P A N E L N E . G I F       0 	        GIF87a  �     			


   !!!"""###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[\\\]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������,       s �H���=�I�p��=�"�g�Ŋ�<DT��ŏ 5�YTg��5cR�L�P�1�Ȝ)�a�5���s�C8&�����gP�D�������c�6���ԩF�N�
�jӬ^���*$  ;  �   4   �� P A N E L N W . G I F       0 	        GIF87a  �     !!!)))111999BBBJJJRRRZZZcccsss{{{���,       L��I�R��{��b8i�_�$�����FU]�A'|��:bH$&r:���D��&�Px*��*;�Z�X�+�����C" ; t   4   �� P A N E L S . G I F         0 	        GIF87a  �  ���BBB111)))                            ,       )0�I��8�ͻ� &�di
C���@�p,Em�xMt��P5+�" ;�  4   �� P A N E L S E . G I F       0 	        GIF87a  �     			


   !!!"""###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[\\\]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������,       h �쁳f�!*HРB<1�D�^��qcF�'~�cǒR�|8���0c�di�E��8sj��E�@�
U2Fe�!�*E)RI�B���jN�X�b ; �   4   �� P A N E L S W . G I F       0 	        GIF87a  �  ���BBB;::333111)))!!!                   ,       H0�IIA��,>7y��ݕ�	�)���Koi� ��pXP���dр1���YRɮX'��r���r����p ; z   4   �� P A N E L W . G I F         0 	        GIF87a  �  ���BBB111)))                            ,       /0�I�(X�,&7y�8^hJd�������v����M�m��"�#�  ;  �	  8   �� Q U E S T I O N . G I F         0 	        GIF89aA : �� ���
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
a���������x��? ')�ZNUx�W�k�N(gP�p�T��q�{:5�}� �&��˝�[���u���y�g��� ��;�a�Foz��(`�WX���ء*��Q�H`���x�����^Y>�����Q�K��燿���Vu��Hb��'}�q>������@rW���'M� �Ǌ���&;���0 A ;   �  <   �� E X C L A M A T I O N . G I F       0 	        GIF89aA : �     �� ��٪!! ��;1��&��z������"��%TL3������^[P��!������$�u3			��}^�� ..-$$#���EEC����ttt��"����
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
�+�~#��苹����H� w���#޳�+и�D�I�4 ��u5K��>޽��!�|��׉�/B�!�J���|^��vIz���������p�CC�#�� S�b�9���ݖ|7�ӡ.u�k�p�(Ll�$ �=�J?��>'7���	Lఈ� L AF.���\j�;�Jv��ypq����H�{h�gA�a0N�^q�C���h�VX ��kp��V�����N�քp�?�`hmg>$j1n6l����Óm���H� . d ��B�L�"���  xP	@��ؠ'����x���P蓟���FIJRn�Q�rؑH ��$2��My����	��<�.w��T>��Bp���� 7���s���f:��|~��"!=���1�r̩x���8�INO5rH9 ����2}���<��t�A  ; :      �� ��     0	                 O K  C a n c e l  Y e s  N o  R e p o s t   f o r m   d a t a ?  M i c r o s o f t   I n t e r n e t   E x p l o r e r       � T h i s   f o r m   i s   b e i n g   s u b m i t t e d   u s i n g   e - m a i l . 
 S u b m i t t i n g   t h i s   f o r m   w i l l   r e v e a l   y o u r   e - m a i l   a d d r e s s   t o   t h e   r e c i p i e n t , 
 a n d   w i l l   s e n d   t h e   f o r m   d a t a   w i t h o u t   e n c r y p t i n g   i t   f o r   p r i v a c y . 
 
 Y o u   m a y   c o n t i n u e   o r   c a n c e l   t h i s   s u b m i s s i o n . � A n   A c t i v e X   c o n t r o l   o n   t h i s   p a g e   i s   n o t   s a f e .     
 Y o u r   c u r r e n t   s e c u r i t y   s e t t i n g s   p r o h i b i t   r u n n i n g   u n s a f e   c o n t r o l s   o n   t h i s   p a g e .     
 A s   a   r e s u l t ,   t h i s   p a g e   m a y   n o t   d i s p l a y   a s   i n t e n d e d . � T h i s   p a g e   p r o v i d e s   p o t e n t i a l l y   u n s a f e   i n f o r m a t i o n   t o   a n   A c t i v e X   c o n t r o l .     Y o u r   c u r r e n t   s e c u r i t y   s e t t i n g s   p r o h i b i t   r u n n i n g   c o n t r o l s   i n   t h i s   m a n n e r .     A s   a   r e s u l t ,   t h i s   p a g e   m a y   n o t   d i s p l a y   c o r r e c t l y .   h      �� ��     0	         D o c u m e n t  % 1 ! s !   D o c u m e n t  % 1 ! s !   ( % 2 ! s !   c o p i e d ) 
 % 1   f r o m   % 2 + N o   d e s c r i p t i o n   i s   a v a i l a b l e   f o r   t h i s   e r r o r .  % 2     - U n e x p e c t e d   c a l l   t o   m e t h o d   o r   p r o p e r t y   a c c e s s .  U n s p e c i f i e d   e r r o r .  I n v a l i d   a r g u m e n t . r C a n ' t   m o v e   f o c u s   t o   t h e   c o n t r o l   b e c a u s e   i t   i s   i n v i s i b l e ,   n o t   e n a b l e d ,   o r   o f   a   t y p e   t h a t   d o e s   n o t   a c c e p t   t h e   f o c u s . $ T h e   c o n t r o l   n e e d s   t o   h a v e   t h e   f o c u s . " T h e   v a l u e   i s   n o t   a   p i c t u r e   o b j e c t .  T h e   p i c t u r e   t y p e   i s   n o t   v a l i d .  I n v a l i d   p r o p e r t y   a r r a y   i n d e x . �      �� ��     0	        � Y o u r   c u r r e n t   s e c u r i t y   s e t t i n g s   p r o h i b i t   r u n n i n g   A c t i v e X   c o n t r o l s   o n   t h i s   p a g e .     A s   a   r e s u l t ,   t h e   p a g e   m a y   n o t   d i s p l a y   c o r r e c t l y .  % 2       @ I n t e r n e t   E x p l o r e r   c a n n o t   d o w n l o a d   f r o m   t h e   I n t e r n e t   s i t e   % 1 . 
 
 % 2   5 T h i s   i t e m   c a n n o t   b e   d i s p l a y e d . 
 
 T r y   a   d i f f e r e n t   i t e m . D C a n n o t   f i n d   ' % 1 ' .   M a k e   s u r e   t h e   p a t h   o r   I n t e r n e t   a d d r e s s   i s   c o r r e c t . ` C a n n o t   s t a r t   t h e   O L E   s e r v e r   f o r   t h i s   t y p e   o f   d o c u m e n t . 
 % 1 
 
 D o   y o u   w a n t   t o   d o w n l o a d   i t   a s   a   f i l e ? ^ T h e   a s s o c i a t e d   O L E   s e r v e r   c a n n o t   l o a d   t h i s   d o c u m e n t . 
 % 1 
 
 D o   y o u   w a n t   t o   d o w n l o a d   i t   a s   a   f i l e ?  S e c u r i t y   A l e r t G Y o u r   c u r r e n t   s e c u r i t y   s e t t i n g s   d o   n o t   a l l o w   t h i s   f i l e   t o   b e   d o w n l o a d e d .  D o w n l o a d   c o m p l e t e 
 % 1 ^ T h e   W e b   p a g e   y o u   a r e   v i e w i n g   i s   t r y i n g   t o   c l o s e   t h e   w i n d o w . 
 
 D o   y o u   w a n t   t o   c l o s e   t h i s   w i n d o w ?   :       �� ��	     0	         F i l e   D o w n l o a d                                 .      �� ��     0	        5 T h i s   i t e m   c a n n o t   b e   d i s p l a y e d . 
 
 T r y   a   d i f f e r e n t   i t e m . x A r e   y o u   s u r e   y o u   w a n t   t o   n a v i g a t e   a w a y   f r o m   t h i s   p a g e ? 
 
 % s 
 
 P r e s s   O K   t o   c o n t i n u e ,   o r   C a n c e l   t o   s t a y   o n   t h e   c u r r e n t   p a g e . � A   s c r i p t   o n   t h i s   p a g e   i s   c a u s i n g   I n t e r n e t   E x p l o r e r   t o   r u n   s l o w l y .     I f   i t   c o n t i n u e s   t o   r u n ,   y o u r   c o m p u t e r   m a y   b e c o m e   u n r e s p o n s i v e . 
 
 D o   y o u   w a n t   t o   a b o r t   t h e   s c r i p t ?  C o u l d   n o t   s a v e   t h e   p i c t u r e .  C o u l d   n o t   s e t   t h e   w a l l p a p e r .                         �      �� ��     0	         I n v a l i d   p r o p e r t y   v a l u e . * T h i s   m e t h o d   c a n ' t   b e   u s e d   i n   t h i s   c o n t e x t . 	 O v e r f l o w .  P e r m i s s i o n   d e n i e d .   C a n   n o t   s e t   p r o p e r t y   a t   r u n t i m e . ) I n v a l i d   t a r g e t   e l e m e n t   f o r   t h i s   o p e r a t i o n & I n v a l i d   s o u r c e   H T M L   f o r   t h i s   o p e r a t i o n E T h e   c o n t r o l   c o u l d   n o t   b e   c r e a t e d   b e c a u s e   i t   i s   n o t   p r o p e r l y   l i c e n s e d .   < T h i s   a d d r e s s   i s   n o t   v a l i d .   C h e c k   t h e   a d d r e s s ,   a n d   t r y   a g a i n . H T h e   s i t e   w a s   n o t   f o u n d .   M a k e   s u r e   t h e   a d d r e s s   i s   c o r r e c t ,   a n d   t r y   a g a i n . e T h e   p r o t o c o l   s p e c i f i e d   i n   t h i s   a d d r e s s   i s   n o t   v a l i d .   M a k e   s u r e   t h e   a d d r e s s   i s   c o r r e c t ,   a n d   t r y   a g a i n . B T h e   s i t e   w a s   f o u n d   b u t   e x c e e d e d   t h e   s y s t e m   l i m i t s   f o r   r e d i r e c t i o n .         �      �� ��
     0	                 D o w n l o a d   c o u l d   n o t   c o m p l e t e ! 	 % 1 ! s ! / S e c  T e m p o r a r y   F o l d e r 	 A l l   F i l e s  S a v i n g :  O p e n i n g :  % 1 ! s !   o f   % 2 ! s !   C o p i e d  % 1 ! d ! % %   o f   % 2 ! s !   C o m p l e t e d  N o t   k n o w n   ( O p e n e d   s o   f a r   % 1 ! s ! ) ) & O p e n   t h i s   f i l e   f r o m   i t s   c u r r e n t   l o c a t i o n  & S a v e   t h i s   f i l e   t o   d i s k     L      �� ��/     0	        5 T h i s   i t e m   c a n n o t   b e   d i s p l a y e d . 
 
 T r y   a   d i f f e r e n t   i t e m . 0 T h i s   i t e m   c a n n o t   b e   d i s p l a y e d . 
 
 T r y   a g a i n   l a t e r . 1 T h i s   i t e m   c a n n o t   b e   f o u n d . 
 
 T r y   a   d i f f e r e n t   i t e m .                           �      �� ��    0	        < T h i s   a d d r e s s   i s   n o t   v a l i d .   C h e c k   t h e   a d d r e s s ,   a n d   t r y   a g a i n . H T h e   s i t e   w a s   n o t   f o u n d .   M a k e   s u r e   t h e   a d d r e s s   i s   c o r r e c t ,   a n d   t r y   a g a i n . e T h e   p r o t o c o l   s p e c i f i e d   i n   t h i s   a d d r e s s   i s   n o t   v a l i d .   M a k e   s u r e   t h e   a d d r e s s   i s   c o r r e c t ,   a n d   t r y   a g a i n . B T h e   s i t e   w a s   f o u n d   b u t   e x c e e d e d   t h e   s y s t e m   l i m i t s   f o r   r e d i r e c t i o n . � T h e   d o w n l o a d e d   f i l e   i s   n o t   a v a i l a b l e .   T h i s   c o u l d   b e   d u e   t o   y o u r   S e c u r i t y   o r   L a n g u a g e   s e t t i n g s   o r   b e c a u s e   t h e   s e r v e r   w a s   u n a b l e   t o   r e t r i e v e   t h e   r e q u e s t e d   f i l e                       