//run(speedAwal, modeSensor, motorKiri, motorKanan, delayBelok, speedTimer, timer)
  followLineMode = antiLeftRight;
  run(0, dimanapun, 60, 60, 800, 0, 0);

  while (1) {
    int cp = scanBarcode();

    switch (cp) {
      case 1:
        Serial.print("OBAT COVID");
        //gripperAction(pick);    //ambil barang
        followLineMode = followRight;
        run(80, dimanapun, 10, 180, 250, 80, 60 );     //putar balik & maju menuju pertigaan
        run(60, sensorTengah, -25, 180, 190, 50, 20);  //pertigaan belok kanan dan maju
        followLineMode = antiLeftRight;
        //run(60, dimanapun, 50, 50, 255, 80, 0);
        //run(60, dimanapun, 0, 0, 255, 80, 0);
        gripperAction(pick);
        run(60, dimanapun, -80, -80, 250, 80, 0);
        followLineMode = followRight;
        run(60, dimanapun, 100, -180, 150, 60, 255);
        run(80, dimanapun, 80, 80, 0, 80, 75);
        followLineMode = followLeft;
        run(60, sensorTengah, 180, -15, 180, 45, 150);
        followLineMode = antiLeftRight;
        run(60, dimanapun, 100, 100, 150, 80, 0);
        ////run(60, dimanapun, 80, 100, 80, 80, 65);
        gripperAction(drop);

        // puter balik geesss
        followLineMode = followRight;
        run(80, dimanapun, -200, 80, 220, 40, 140);
        followLineMode = followLeft;
        run(60, sensorTengah, 180, 10, 200, 60, 150);

        break;
      case 2:
        Serial.print("VAKSIN");
        //        gripperAction(pick);    //ambil barang
        followLineMode = followLeft;
        run(0, dimanapun, 70, -40, 550, 80, 3);     //putar balik & maju menuju pertigaan
        run(80, tanpaGaris, -35, 100, 200, 100, 0);  //pertigaan belok kanan dan maju
        followLineMode = antiLeftRight;
        // run(80, dimanapun, 50, 100, 100, 80, 100);    //pindah mode jadi anti left right
        followLineMode = followRight;
        // run(80, dimanapun, 100, 50, 100, 80, 50);    //pindah mode jadi follow right
        // run(80, tanpaGaris, 150, -20, 300, 30, 30);   //pertigaan belok kanan dan maju sebelum naruh

        gripperAction(drop);
        break;
    }
    break;
  }
