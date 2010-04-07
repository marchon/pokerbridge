/* LICENSE NOTICE
	Copyright (c) 2008, Frederick Emmott <mail@fredemmott.co.uk>

	Permission to use, copy, modify, and/or distribute this software for any
	purpose with or without fee is hereby granted, provided that the above
	copyright notice and this permission notice appear in all copies.

	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
	WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
	MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
	ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
	WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
	ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
	OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
#ifndef _JSONQT_JSON_TO_VARIANT_H
#define _JSONQT_JSON_TO_VARIANT_H

/** Qt-based JSON handling.
 * This is based on a recursive descent parser with 1-character lookahed,
 * and follows the structure of the grammar presented on json.org as closely
 * as possible, to avoid mistakes, and hopefully to make the code more readable.
 *
 * @author Fred Emmott <mail@fredemmott.co.uk>
 */
/** Parsing exception class.
 * Raised whenever JsonQt can't pass something it's been given, for
 * whatever reason.
 */
class PB_EXPORT JsonParseException : public std::exception
{
	public:
		/** Create a ParseException.
		 * @param got is what was found in the string.
		 * @param expected is what the parser was expecting.
		 * @param remaining is what was left of the input.
		 */
		JsonParseException(
			const QString& got,
			const QString& expected,
			const QString& remaining
		) throw();
		~JsonParseException() throw();

		/// A single string providing information on the
		/// exception.
		virtual const char* what() const throw();

		/// What the parser found.
		QString got();
		/// What the parser was expecting.
		QString expected();
		/// The remaining unparsed input.
		QString remaining();
	private:
		QString m_got;
		QString m_expected;
		QString m_remaining;
		static QString m_text;
};

/** Class for converting JSON strings to QVariant-based structures.
 *
 * @author Fred Emmott <mail@fredemmott.co.uk>
 */
class PB_EXPORT JsonToVariant
{
    public:
        /** Main parsing function.
         *
         * @param json is a string containing JSON text.
         * @returns A QVariant-representation of the JSON
         * 	structure.
         * @throws JsonParseException if the string provided is not
         * 	valid JSON (or at least this parser thinks it
         * 	isn't ;) )
         */
        static QVariant parse(const QString& json) throw (JsonParseException);

        /** Parse multiple objects in one string.
         * This is useful when working on streams where
         * one-chunk-per-json-object is not guaranteed.
         */
        static QList<QVariantMap> multiParse(const QString& json) throw(JsonParseException);
    private:
        JsonToVariant();
        // Parsers for types given on JSON.org
        QVariantMap parseObject();
        QVariantMap parseMembers();
        QPair<QString, QVariant> parsePair();
        QVariantList parseArray();
        QVariantList parseElements();
        QVariant parseValue();
        QString parseString();
        QString parseChars();
        QChar parseChar();
        QVariant parseNumber();
        QString parseInt();
        QString parseFrac();
        QString parseExp();
        QString parseDigits();
        QString parseE();

        // Parsers for types implied on JSON.org
        QChar parseDigit();
        QChar parseHexDigit();
        bool parseBool();
        QVariant parseNull();

        // Internal functions
        /// The unparsed part of the input string.
        inline QString remaining();

        /** Consume the next character.
         * Advances m_sym to the next character, and returns it.
         * Optionally skips over whitespace.
         *
         * @param skipWhitespace controls if whitespace is
         * 	ignored.
         * @returns *m_sym
         * @throws JsonParseException if the end of the string is
         *	reached.
         */
        QChar consume(bool skipWhitespace = true)
            throw(JsonParseException);

        /** Consume the next character, and check for equality
         * with the specified character.
         *
         * @param wanted is the character to compare to.
         * @throws JsonParseException if the end of the string is
         * 	reached, or the characaters are not equal.
         */
        void consume(QChar wanted) throw(JsonParseException);

        /// Convenience function for consume(QChar).
        void consume(char wanted) throw(JsonParseException);

        /** Attempt to consume the specified string.
         * This attempts to consume length(wanted) characters,
         * including whitespace, and checks that they are equal
         * to the characters in the same position in the
         * specified string.
         *
         * @param wanted is the string to attempt to consume.
         * @throws JsonParseException if the end of the string is
         * 	reached, or the string comparisson fails.
         */
        void consume(QString wanted) throw(JsonParseException);

        /** Try to consume a single character, without throw.
         * This will try to read a single character, and
         * compares to the specified character.
         *
         * @param wanted is the character to compare to.
         * @returns true if the character specified was
         * 	successfully consumed.
         * @returns false if the end of the string was reached,
         * 	or the characters were not equal.
         */
        bool tryConsume(QChar wanted) throw();

        /** Return the next symbol.
         * Optionally skips whitespace.
         * 
         * @param skipWhitespace sets the whitespace handling.
         * @returns the next symbol.
         * @throws JsonParseException if the end of the string is
         * 	reached.
         */
        QChar peekNext(bool skipWhitespace = true)
            throw(JsonParseException);

        // Variables

        /// Iterator pointing at the current symbol.
        QString::ConstIterator m_sym;
        /// Iterator pointing at the next symbol.
        QString::ConstIterator m_next;
        /// Iterator pointing at the end of the string.
        QString::ConstIterator m_end;
};

class PB_EXPORT VariantToJson
{
public:
	static QString toJson(QVariantMap v);
	static QString toJson(QVariantList v);
	static QString toJson(QVariant v);
};

class PB_EXPORT JsonReader: public QObject
{
Q_OBJECT;
public:
    JsonReader(QObject *parent = 0);
    void setInput(QIODevice *dev);

signals:
    void parsed(QVariantMap msg);
public:
    bool parse();
    QVariant lastParsed();
protected:
    int braces;
    bool inString;
    bool inEscape;
    bool started;
    QIODevice *input;
    QVariant value;
    QString json;
};


class PB_EXPORT ObjectVariant
{
public:
	static void objectToVariant(QVariantMap &map, QObject *obj);
	static void variantToObject(const QVariantMap &map, QObject *obj);
	static QString toShortString(QVariantMap &map);
};

#endif
