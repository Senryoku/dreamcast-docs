����  -� Code 
SourceFile ConstantValue 
Exceptions CoolHeadLines  java/applet/Applet  Ljava/lang/Thread; m_CoolHeadLines 
 		   ()V stop   java/lang/Thread 
   Ljava/awt/Dimension; m_dimAppletSize  	   I height   java/awt/Dimension 	   m_iFontHeight  	   Z m_fStoppedScrolling !  	  " m_iOldMessageSelected $ 	  % ()Ljava/awt/Graphics; getGraphics ( ' java/awt/Component *
 + ) m_iOldMessageSelectedYOffset - 	  . Ljava/awt/FontMetrics; m_fm 1 0	  2 ()I 
getDescent 5 4 java/awt/FontMetrics 7
 8 6 Ljava/awt/Color; m_colTextColor ; :	  < )(Ljava/awt/Graphics;IIILjava/awt/Color;)V 
drawString ? >
  @ Ljava/util/Vector; 
m_vectData C B	  D (I)Ljava/lang/Object; 	elementAt G F java/util/Vector I
 J H TextJump L ()Ljava/lang/String; 	getString O N
 M P [Ljava/lang/String; R java/lang/String T 	BackColor V String X Background Color Z 	TextColor \ 
Text Color ^ HiliteTextColor ` Hilited Text Color b ScrollDelay d int f msec delay between each scroll h MessageDelay j sec delay between each message l NumItems n Number of items p 	URLPrefix r !Prefix for all .htm or .asp files t (C)I 	charWidth w v
 8 x (II)I min { z java/lang/Math }
 ~ | Ljava/awt/Font; m_font � �	  � (Ljava/awt/Font;)V setFont � � java/awt/Graphics �
 � � (Ljava/awt/Color;)V setColor � �
 � � (Ljava/lang/String;II)V ? �
 � � (IIII)V fillOval � �
 � � (I)Ljava/lang/String; getStringFromVector � �
  � :(Ljava/awt/Graphics;Ljava/lang/String;IILjava/awt/Color;)V ? �
  � (Ljava/lang/Runnable;)V <init> � �
  � start � 
  � drawHeadlines � 
  � java/lang/StringBuffer � � 
 � � Name: CoolHeadLines
 � ,(Ljava/lang/String;)Ljava/lang/StringBuffer; append � �
 � � 0Author: Michael Howard (mikehow@microsoft.com)
 � -Created with Microsoft Visual J++ Version 1.1 � toString � N
 � �
  � Ljava/lang/String; PARAM_BackColor � �	  � PARAM_TextColor � �	  � PARAM_HiliteTextColor � �	  � PARAM_ScrollDelay � �	  � PARAM_MessageDelay � �	  � PARAM_NumItems � �	  � PARAM_URLPrefix � �	  � m_iScrollDelay � 	  � m_iMessageDelay � 	  � m_iCurrentMessage � 	  � java/awt/Color � (III)V � �
 � � m_colBackColor � :	  � m_colHiliteTextColor � :	  � size � 4
 J � scrollOneLine � 
  � m_iMaxMessage � 	  � LDoubleBuffer; m_buff � �	  � DoubleBuffer �
 � ) ()Ljava/awt/Rectangle; getSize � �
 � � java/awt/Rectangle �	 �  (I)I 
getYOffset � �
  � suspend � 
  � m_strURLPrefix  �	  / getURL N
 M (Ljava/lang/String;)V 
showStatus	
 
 ()Ljava/applet/AppletContext; getAppletContext
  java/net/URL �
 (Ljava/net/URL;)V showDocument java/applet/AppletContext java/net/MalformedURLException java/util/StringTokenizer
 	nextToken N
  (Ljava/lang/String;)I parseInt#" java/lang/Integer%
&$ (J)V sleep)(
 * java/lang/InterruptedException,
   &(Ljava/lang/String;)Ljava/lang/String; getParameter0/
 1 $(Ljava/lang/String;)Ljava/awt/Color; getColorFromRGB43
 5 m_iNumItems7 	 8 ()Ljava/awt/Dimension; �:
 +; java/awt/Font= 	Helvetica? � �
>A '(Ljava/awt/Font;)Ljava/awt/FontMetrics; getFontMetricsDC
 +E getMaxDescentG 4
 8H 
getLeadingJ 4
 8K getMaxAscentM 4
 8N widthP 	 Q � �
 �S +(Ljava/applet/Applet;Ljava/awt/Rectangle;)V �U
 �V xX 	 �Y y[ 	 �\	 �Q fillRect_ �
 �` setBackgroundb �
 +c
 J �
 U � Textg (I)Ljava/lang/StringBuffer; �i
 �j URLl '(Ljava/lang/String;Ljava/lang/String;)V �n
 Mo (Ljava/lang/Object;)V 
addElementrq
 Js ()Ljava/awt/Image; getImagevu
 �w 3(Ljava/awt/Image;IILjava/awt/image/ImageObserver;)Z 	drawImagezy
 �{  at }
 java/lang/Runnable� CoolHeadLines.java run getAppletInfo getParameterInfo ()[[Ljava/lang/String; init 	mouseMove (Ljava/awt/Event;II)Z 	mouseExit 	mouseDown    �   � �      W  � �      ]  � �      a  � �      e  � �      k  � �      o  � �      s  � :    ; :    � :    �     �    7      �    
 	         C B    � �    1 0         � �    !      �     �     $     -                  *� � *� � *� �      � �          *� � d*� l=�     ��     O     C*� #� �*� &� 4**� ,*� &*� � *� /*� hd*� 3� 9d`*� =� A*� &�      � �          *� E� K� MM,� Q�     ��     �     �� SY� UYWSYYSY[SSY� UY]SYYSY_SSY� UYaSYYSYcSSY� UYeSYgSYiSSY� UYkSYgSYmSSY� UYoSYgSYqSSY� UYsSYYSYuSSL+�      ? �     U     I*� 3W� y6l*� l� 6+*� �� �+� �+,`� �+l`dd� ��      ? >          *+*� �� ��      �      ,      *� � *� Y*� �� *� � ��*� ��     � N     &     � �Y� ��� ��� ��� �� ��      �      �     {*� �*W� �*]� �*a� �*e� �*k� �*o� �*s� �*
� �*� �*� �*� &*� /*� �Y � � �� ۵ �*� �Y� ۵ =*� �Y �� ۵ �      �      l     `*Y� �`� �*Y� �*� E� �p� �*� ֚ <� 
*� �*� ���**� � �*� �*� � �� �*� 3� 9d*� =� A*� �     ��     }     i*� #� �*� �6*� �d6*� � �� �Y� �*�� �� �*� E� K� M�� �� �:*�*��Y�� � W�   c f   43     <     0�Y+�M,�!�'>,�!�'6,�!�'6� �Y� ۰     �      C     /*� #*� &*� /*� �*� #*� ��h��+���W*�.���    $ '-   �     �    �*W�2L+� **+�6� �*]�2L+� **+�6� =*a�2L+� **+�6� �*e�2L+� *+�'� �*k�2L+� *+�'� �*o�2L+� *+�'�9*s�2L+� *+�**�<� *�>Y@�B� �***� ��F� 3**� 3�I*� 3�L`*� 3�O`� � �Y*� �R*� � *� `�TM*� �Y*,�W� �*� � �*� ޶ �*� � �,�Z,�],�^,� ��a**� ޶d**� � *� l`� �*� JY�e� E>� ^� UY�f:*� �Y� �h� ��k� ��2:� UY�f:*� �Y� �m� ��k� ��2:*� E� MY�p�t�*�9����      �      �     r<� %*� ,*� �xt*�|W*� Ѕ�+� W�*� ���*� � �L+*� �x*� t*�|W+*� ޶ �+*� � *� �R*� � *� `�a�     #-   ��     �     �*� #� �*� �6*� �d6*� &� �*� &� 9**� ,*� &*� � *� /*� hd*� 3� 9d`*� =� A� *� &� |*� &*� /**� ,*� � *� hd*� 3� 9d`*� � A� �Y� �*� �� �~� �*�� �� �*� E� K� M�� �� �:*�� �         �