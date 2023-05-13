#ifndef FORMATDIALOG_H
#define FORMATDIALOG_H

#include <QApplication>
#include <QDialog>
#include <QTextEdit>
#include <QFontComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QButtonGroup>
#include <QLabel>

class FormatDialog : public QDialog
{
    Q_OBJECT
public:
    FormatDialog(QWidget *parent = nullptr);
    void initDialog(QTextEdit *textEdit);

private slots:
    void applyFormat();
    void chooseColor();

private:
    QTextEdit *m_textEdit;
    QFontComboBox *m_fontComboBox;
    QSpinBox *m_fontSizeSpinBox;
    QButtonGroup *m_alignmentGroup;
    QCheckBox *m_boldCheckBox;
    QCheckBox *m_italicCheckBox;
    QCheckBox *m_underlineCheckBox;
    QColor m_color;
    Qt::Alignment m_alignment;
    QLabel *m_colorLabel;
};

#endif // FORMATDIALOG_H
