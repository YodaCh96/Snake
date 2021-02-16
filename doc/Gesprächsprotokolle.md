# Sitzungsprotokoll

**Datum**: *17.05.2017*
**Protokollführer**: *Reindl Dominik*

**Anwesende**:

- Diogo Abreu
- Noah Eggenberger
- Ioannis Christodoulakis
- Dominik Reindl

**Traktanden**:

- **Datenstruktur für Spiellogik besprechen / abnehmen**
  - Wir haben die Datenstruktur der Spiellogik durchgearbeitet.
Es gab eine Anpassung bei der Grösse des Arrays welches wir festgelegt haben. Anstatt ein Array der Grösse 16 x 8, wird es noch eine Reihe an jeder Seite angefügt so, dass es ein Raster von 18 x 10 ergibt. Mit diesem Array ist es für Noah einfacher die Spielelogik zu programmieren. Zusätzlich wurde besprochen, dass nach Spielende zwei Zahlen auf der Matrix angezeigt werden sollen, welche die gesammelte Punktzahl ersichtlich machen. Die Zahl wird nach Spielende in der Spiellogik im Array eingespeist. Entscheid: Array wird vergrössert auf 18 x 10.
- **Datumfestlegung Fertigstellung der Software von der Spiellogik**
  - Wir bekommen die Spiellogik auf Sketch (Code für Arduino) mit der besprochenen Struktur am Abend vom 17.05.2017.
- **Definierte Testfälle besprechen / abnehmen**
  - Die Testfälle haben wir in unserer Dokumentation definiert.

---

**Datum**: *07.06.2017*
**Protokollführer**: *Reindl Dominik*

**Anwesende**:

- Diogo Abreu
- Noah Eggenberger
- Ioannis Christodoulakis
- Dominik Reindl

**Traktanden**:

- **Neuer Abgabetermin Software, Spiellogik**
  - Leider gabt es beim Erstellen der Spiellogik auf der Software-Seite Probleme. Durch das wurde der Abgabetermin erneut verschoben. Damit wir nicht zu stark in Verzug kommen, haben wir beschlossen das Arbeitspaket Hardware dem Arbeitspaket Software vorzuziehen.
- **Abänderung der Auslese-Software**
  - Wir haben gesehen, dass das Array für die Ansteuerung nicht das gewünschte Muster aufweist. Wir haben uns angeschaut wie wir dieses Problem am einfachsten gelöst wird. Wir kamen auf den Entschluss bei der Auslese-Software das Array so zu konvertieren dass es unseren Angaben entspricht.

---

**Datum**: *21.06.2017*
**Protokollführer**: *Reindl Dominik*

**Anwesende**:

- Diogo Abreu
- Noah Eggenberger
- Ioannis Christodoulakis
- Dominik Reindl

**Traktanden**:

- **Übergeben von Libraries**
  - Die Libraries können übernommen werden.
- **Spielelogik und Ausgebelogik zusammenführen**
  - Abstimmung von der Spiel- und Ausleselogik war leider nicht korrekt. So wie die Spiellogik aufgebaut ist, wird unsere Ausleselogik falsch ausgeführt. Entscheid: Wir schreiben die Spiellogik um. So das unsere Ausleselogik und die Spiellogik parallel ausgeführt werden. So ist es möglich, dass wir ohne Unterbruch der Ausleselogik die LED-Matrix ansteuern.
