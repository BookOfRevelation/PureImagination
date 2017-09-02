#ifndef SLIDESPINER_H
#define SLIDESPINER_H

#include <QWidget>
#include <QBoxLayout>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QLabel>

/**
 * @brief This class implements a simple SpinBox,
 * related to a Slider.
 * It's constructed given a min and a max (by default,
 * 0 to 360 in order to represent an angle).
 * The precision parameter is used to set the precision of
 * the value (i.e : precision 1 will allow integer values only).
 *
 * As Qt doesn't natively manage floating point values with QSlider,
 * the precision parameter multiplies the expected values by
 * a power of 10, in order to recreate the illusion of floating point.
 *
 */

class SlideSpiner : public QWidget
{
    Q_OBJECT
public:

    explicit SlideSpiner(const QString& name, const QString& unitName, int precision = 1, double min = 0, double max = 360, QWidget *parent = 0);

    /**
     * @brief getValue : Get the current double value.
     * @return
     */
    double getValue() const;

    /**
     * @brief setToMiddle : Set the default value to the mean.
     */
    void setToMiddle();

    /**
     * @brief setMaximum : Set the maximum value.
     */
    void setMaximum(double max);
    void setMinimum(double min);

    double getMinimum() const
    {
        return this->spinBox->minimum();
    }
    double getMaximum() const
    {
        return this->spinBox->maximum();
    }


    /**
     * @brief setValue : Set the value at the
     * given parameter.
     * @param val : the value.
     */
    void setValue(double val);

private:

    QBoxLayout* mainLayout;
    QDoubleSpinBox* spinBox;
    QSlider* slider;
    QLabel* header;
    QLabel* unit;

    double powFactor;



signals:

    void valueChanged(double value);

public slots:

    /**
     * @brief spinToSlide : Called whenever the spiner value changed
     * in order to update the slider as well.
     * @param value
     */
    void spinToSlide(double value);

    /**
     * @brief slideToSpin : Called whenever the slider value changed
     * in order to update the spiner as well.
     * @param value
     */
    void slideToSpin(int value);


};

#endif // SLIDESPINER_H
