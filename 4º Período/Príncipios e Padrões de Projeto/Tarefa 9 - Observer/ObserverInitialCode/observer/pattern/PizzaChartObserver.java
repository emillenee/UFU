package observer.pattern;

import observer.CourseRecord;
import observer.LayoutConstants;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.util.Vector;
import javax.swing.*;

public class PizzaChartObserver extends JPanel implements Observer {
    private Vector<CourseRecord> courseData;

    public PizzaChartObserver(CourseData data) {
        data.attach(this);
        this.courseData = data.getUpdate();
        this.setPreferredSize(new Dimension(100, 400));
        this.setBackground(Color.white);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        int radius = 100;

        double total = 0.0;
        for(CourseRecord record : courseData) {
            total += record.getNumOfStudents();
        }

        if(total == 0.0) return;

        double startAngle = 0.0;

        for(int i = 0; i < courseData.size(); i++) {
            CourseRecord record = courseData.get(i);
            double ratio = (record.getNumOfStudents() / total) * 360.0;
            g.setColor(LayoutConstants.courseColours[i % LayoutConstants.courseColours.length]);
            g.fillArc(LayoutConstants.xOffset, LayoutConstants.yOffset + 100, 2 * radius, 2 * radius, (int) startAngle, (int) ratio);
            startAngle += ratio;
        }
    }

    @Override
    public void update(Observable o) {
        CourseData data = (CourseData) o;
        this.courseData = data.getUpdate();

        this.setPreferredSize(new Dimension(2 * LayoutConstants.xOffset
                + (LayoutConstants.barSpacing + LayoutConstants.barWidth)
                * this.courseData.size(), LayoutConstants.graphHeight + 2
                * LayoutConstants.yOffset));
        this.revalidate();
        this.repaint();
    }
}
