/*
Copyright (C) 2011-2012, Northern Digital Inc. All rights reserved.
 
All Northern Digital Inc. (�NDI�) Media and/or Sample Code and/or Sample Code
Documentation (collectively referred to as �Sample Code�) is licensed and provided "as
is� without warranty of any kind. The licensee, by use of the Sample Code, warrants to
NDI that the Sample Code is fit for the use and purpose for which the licensee intends to
use the Sample Code. NDI makes no warranties, express or implied, that the functions
contained in the Sample Code will meet the licensee�s requirements or that the operation
of the programs contained therein will be error free. This warranty as expressed herein is
exclusive and NDI expressly disclaims any and all express and/or implied, in fact or in
law, warranties, representations, and conditions of every kind pertaining in any way to
the Sample Code licensed and provided by NDI hereunder, including without limitation,
each warranty and/or condition of quality, merchantability, description, operation,
adequacy, suitability, fitness for particular purpose, title, interference with use or
enjoyment, and/or non infringement, whether express or implied by statute, common law,
usage of trade, course of dealing, custom, or otherwise. No NDI dealer, distributor, agent
or employee is authorized to make any modification or addition to this warranty.

In no event shall NDI nor any of its employees be liable for any direct, indirect,
incidental, special, exemplary, or consequential damages, sundry damages or any
damages whatsoever, including, but not limited to, procurement of substitute goods or
services, loss of use, data or profits, or business interruption, however caused. In no
event shall NDI�s liability to the licensee exceed the amount paid by the licensee for the
Sample Code or any NDI products that accompany the Sample Code. The said limitations
and exclusions of liability shall apply whether or not any such damages are construed as
arising from a breach of a representation, warranty, guarantee, covenant, obligation,
condition or fundamental term or on any theory of liability, whether in contract, strict
liability, or tort (including negligence or otherwise) arising in any way out of the use of
the Sample Code even if advised of the possibility of such damage. In no event shall
NDI be liable for any claims, losses, damages, judgments, costs, awards, expenses or
liabilities of any kind whatsoever arising directly or indirectly from any injury to person
or property, arising from the Sample Code or any use thereof.
*/

#ifndef __vtkTrackerWidget_h
#define __vtkTrackerWidget_h

#include "vtkTrackerWidget_global.h"

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "ndXfrms.h"

class vtkTracker;
class vtkTrackerSettingsDialog;
class vtkTrackerWidgetXfrmCallback;

class VTKTRACKERWIDGET_EXPORT vtkTrackerWidget : public QWidget
{
  Q_OBJECT

public:
  vtkTrackerWidget( QWidget *parent = 0);
  ~vtkTrackerWidget();

  QSize sizeHint() const;

  inline vtkTracker* getTracker() {return m_Tracker;}
  void UpdateToolTransform(int port, QString status);
  void UpdateToolTransform(int port, QuatTransformation xfrm);
  void UpdateToolTransform(int port, QuatTransformation xfrm, double effFreq, double quality);

public slots:
  virtual void OnConfigureTracker();
  virtual void OnConfigureTrackerAccepted();
  virtual void OnStartTracker();
  virtual void OnStopTracker();
  virtual void UpdateData();

signals:
  void TrackerConfigured(QString SerialNumber);
  void TrackerStarted();
  void TrackerStopped();
  void ToolTransformUpdated(int port, QString status);
  void ToolTransformUpdated(int port, QuatTransformation xfrm);
  void ToolEffectiveFrequencyUpdated(int port, double freq);
  void ToolQualityNumberUpdated(int port, double quality);

private:
  // some helper functions.
  void setupUi();
	void setupUiLayout();
  void CreateActions();
  void ConfigureTracker();
  void PopUpError(QString str);

  // the owner of this widget.
  QWidget *m_Parent;
  
  // GUI variables.
  //Ui::vtkTrackerWidget m_GUI;
  QPushButton *m_ConfigureTrackerButton;
  QPushButton *m_StartTrackingButton;
  QPushButton *m_StopTrackingButton;
  //QVBoxLayout *m_VerticalLayout;

  
  // actual tracker object we are controlling.
  vtkTracker *m_Tracker;
  vtkTrackerSettingsDialog *m_TrackerSettingsDialog;

  // keep track of the tools.
  std::vector < QuatTransformation > m_xfrms;
  std::vector < double > m_effectiveFrequencies;
  std::vector < double > m_quality;
  std::vector < vtkTrackerWidgetXfrmCallback* > m_xfrmCallbacks;

  //timer.
  QTimer *m_Timer; // need a timer to update the tracker.
  double m_TrackerUpdateFrequency;
};

#endif