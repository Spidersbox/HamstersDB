#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QtCore>
#include <QtGui/QtGui>

#include <QApplication>
#include <QDesktopWidget>
#include <QVariant>
#include <QSettings>
//#include <QCommandLineParser>
#include <QPushButton>
#include <QMainWindow>
//#include <QMediaPlayer>
//#include <QMediaMetaData>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>

#include <QMimeData>
#include <QDragEnterEvent>
#include <QDrag>
#include <QDropEvent>
#include <QKeyEvent>
#include <QDir>
#include <QSlider>

//#include <initguid.h>
//#include "wmp.h"


#include <dbmanager.h>

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QTimer>

//#include <dialogaboutme.h>

#include <iostream>
//#include <Windows.h>

#include <QSystemTrayIcon>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
    
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  struct activeSettings
  {
    bool paused;// = false;
    bool mute;// = false;
    int volume;// = 55;
    int currentId;// = 0;
    int current_index;// = 0;
    int selected_index;// = 0;
    int selected_id;// = -1;
    bool repeatCurrentMusic;// = false;
    bool repeatList;// = false;
    bool shuffle;// = false;
    QString dosya;// = "";
  };

  struct Music
  {
    int id;// = 0;
    QString name;// = "";
    QString path;// = "";
    int lenghtAsSecond;// = 0;
    QString lenghtToShow;// = "";
  };

  struct Duration
  {
    int musicId;// = 0;
    QString path;// = "";
    int lenghtAsSecond;// = 0;
    QString lenghtToShow;// = "";
  };

  activeSettings _activeSettings;
  Duration _musicDuration;

    
private:
  Ui::MainWindow *ui;
  QSystemTrayIcon *mSystemTrayIcon;

private slots:

//  void mediaStatuChngd(QMediaPlayer::MediaStatus state);
//  void on_positionChanged(qint64 position);
//  void on_durationChanged(qint64 position);

//  void on_playerForDuration_durationChanged(qint64 position);
//  void fnc_getMusicDurationAsync();
//  void pbVolume_valueChanged(int value);

//  void on_btnDosyaSec_clicked();

//  void on_lstMusic_doubleClicked(const QModelIndex &index);
//  int getMusicDurationAsSecond(QString &filePath);

//  void on_pbMusic_sliderMoved(int position);
//  void updateWindowTitle(const QString &state);
//  void fnc_btnMuteClick();
//  void fnc_setShuffle();
//  void fnc_setRepeatList();
//  void fnc_setRepeatCurrent();
//  void fnc_getSettings();
//  void fnc_setSettings();
//  void fnc_btnPlay_clicked();
//  void fnc_lstMusic_singleClicked(const QModelIndex &index);
//  void fnc_pbVolumeReleased();
//  void fnc_nextMusic();
//  void fnc_previousMusic();
//  void fnc_changeMusic();
//  void fnc_searchMusic(const QString &text);
//  void fnc_aboutMe();
//  void fnc_exitProgram();
//  void fnc_showMusicInf();
//  void fnc_exportPlaylist();
//  void fnc_importPlaylist();
//  void fnc_clearList();

//  void on_pbMusic_sliderReleased();

  void on_comboBox_editTextChanged(const QString &arg1);

public slots:
  void on_lineEdit_textEdited(const QString &arg1);

signals:
//  void musicAdded();
};

class MySlider : public QSlider
{
protected:
  void mousePressEvent ( QMouseEvent * event )
  {
    if (event->button() == Qt::LeftButton)
    {
      if (orientation() == Qt::Vertical)
        setValue(minimum() + ((maximum()-minimum()) * (height()-event->y())) / height() ) ;
      else
        setValue(minimum() + ((maximum()-minimum()) * event->x()) / width() ) ;

      event->accept();
    }
    QSlider::mousePressEvent(event);
  }
};

#endif // MAINWINDOW_H
