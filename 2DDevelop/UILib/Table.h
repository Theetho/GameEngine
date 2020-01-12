#pragma once

#include "Input.h"

namespace UILib
{
	class Table;

	struct Cellule : public UIElement
	{
		Cellule(const std::string& label)
			: UIElement(sf::Vector2f(0.f, 0.f), nullptr, label)
		{
			mShape.setFillColor(sf::Color::Transparent);
			mShape.setOutlineColor(sColor["Outline"]);
			mShape.setOutlineThickness(1);
		
			UpdateFontSize();
			CenterText(mLabel);
		}
		Cellule(const Cellule& cellule)
			: UIElement(cellule.mShape.getPosition(), cellule.mCallback, cellule.mLabel.getString().toAnsiString())
		{
			mShape.setFillColor(sf::Color::Transparent);
			mShape.setOutlineColor(sColor["Outline"]);
			mShape.setOutlineThickness(1);
			
			UpdateFontSize();
			CenterText(mLabel);
		}
		Cellule(const Cellule&& cellule) noexcept
			: UIElement(cellule.mShape.getPosition(), cellule.mCallback, cellule.mLabel.getString().toAnsiString())
		{
			mShape.setFillColor(sf::Color::Transparent);
			mShape.setOutlineColor(sColor["Outline"]);
			mShape.setOutlineThickness(1);

			UpdateFontSize();
			CenterText(mLabel);
		}
		Cellule& operator=(const Cellule& cellule)
		{
			mShape    = cellule.mShape;
			mCallback = cellule.mCallback;
			mLabel    = cellule.mLabel;
		}
		Cellule&& operator=(const Cellule&& cellule) noexcept
		{
			mShape	  = cellule.mShape;
			mCallback = cellule.mCallback;
			mLabel    = cellule.mLabel;
		}

		void OnUpdate() override { }
	private:
		friend class UILib::Table;
		Cellule(const std::string& label, const sf::Vector2f& position)
			: UIElement(position, nullptr, label)
		{
			mShape.setFillColor(sf::Color::Transparent);
			mShape.setOutlineColor(sColor["Outline"]);
			mShape.setOutlineThickness(1);
		
			UpdateFontSize();
			CenterText(mLabel);
		}

		void UpdateFontSize()
		{
			float size = mLabel.getCharacterSize();

			// Get the minimum size for the font
			while (mLabel.getGlobalBounds().width > mShape.getSize().x)
			{
				--size;
				mLabel.setCharacterSize(size);
			}

			// Set the font size even more little
			mLabel.setCharacterSize(size - 2);
		}
		void SetSize(const sf::Vector2f& size)
		{
			mShape.setSize(size);
		}
		sf::Vector2f GetPosition() const
		{
			return mShape.getPosition();
		}
	};

	class Table : public UIElement
	{
	public:
		Table(const std::vector<std::string>& header, const sf::Vector2f& size, const sf::Vector2f& position, std::function<void()> callback, const std::string& label)
			: UIElement(position, callback, label)
			, mTable()
			, mCelluleWidth(size.x / (float)header.size())
		{
			float x = position.x;
			float y = position.y;
			
			mTable.push_back(std::vector<Cellule>());
			for (auto& name : header)
			{
				mTable.back().push_back(Cellule(name, sf::Vector2f(x, y)));
				mTable.back().back().SetSize(sf::Vector2f(mCelluleWidth, mCelluleHeight));
				x += mCelluleWidth;
			}
			
			mShape.setSize(size);
		}

		Table(const std::vector<std::vector<Cellule>>& values, const sf::Vector2f& size, const sf::Vector2f& position, std::function<void()> callback, const std::string& label)
			: UIElement(position, std::move(callback), label)
			, mTable()
			, mCelluleWidth(size.x / (float)values[0].size())
			, mCelluleHeight(size.y / (float)values.size())
		{
			float x = position.x;
			float y = position.y;
			// Default header
			mTable.push_back(std::vector<Cellule>());
			for (int i = 0; i < values[0].size(); ++i)
			{
				Cellule cellule = Cellule("Column " + std::to_string(i), sf::Vector2f(x, y));
				cellule.SetSize(sf::Vector2f(mCelluleWidth, mCelluleHeight));
				mTable[0].push_back(cellule);
				x += mCelluleWidth;
			}
			y += mCelluleHeight;
			for (int i = 1; i < values.size(); ++i)
			{
				x = position.x;
				mTable.push_back(std::vector<Cellule>());
				for (int j = 0; j < values[0].size(); ++j)
				{
					mTable[i].push_back(values[i][j]);
					mTable[i].back().SetSize(sf::Vector2f(mCelluleWidth, mCelluleHeight));
					mTable[i].back().SetPosition(sf::Vector2f(x, y));
					x += mCelluleWidth;
				}
				y += mCelluleHeight;
			}
			mShape.setSize(size);
		}
		~Table()
		{}

		void OnUpdate() override
		{
			for (auto& row : mTable)
			{
				for (auto& column : row)
				{
					column.OnUpdate();
				}
			}
		}

		void Clear()
		{
			for (auto& row : mTable)
			{
				row.clear();
			}
			mTable.clear();
		}

		void ClearData()
		{
			for (int row = mTable.size() - 1; row > 0; --row)
			{
				mTable[row].clear();
				mTable.pop_back();
			}
			UpdateCellule();
		}

		void SetHeader(const std::vector<std::string>& header)
		{
			for (int i = 0; i < std::min(header.size(), mTable[0].size()); ++i)
			{
				mTable[0][i] = header[i];
			}
		}

		void SetHeader(unsigned int index, const std::string& header)
		{
			if (index >= mTable[0].size())
				return;
			mTable[0][index] = header;
		}

		void SetRow(unsigned int index, const std::vector<Cellule>& value)
		{
			for (int i = 0; i < std::min(value.size(), mTable[0].size()); ++i)
			{
				sf::Vector2f position = mTable[index][i].GetPosition();
				mTable[index][i] = value[i];
				mTable[index][i].SetPosition(position);
			}
		}

		void SetColumn(unsigned int index, const std::vector<Cellule>& value)
		{
			for (int i = 0; i < std::min(value.size(), mTable.size()); ++i)
			{
				sf::Vector2f position = mTable[i][index].GetPosition();
				mTable[i][index] = value[i];
				mTable[i][index].SetPosition(position);
			}
		}

		void AddRow(const std::vector<Cellule>& value)
		{
			if (value.size() != mTable[0].size())
				return;

			mTable.push_back(value);
			UpdateCellule();
		}

	private:
		std::vector<std::vector<Cellule>> mTable;
		float mCelluleWidth = 50.0f, mCelluleHeight = 20.f;
		// Inherited from Drawable
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			UIElement::draw(target, states);
			for (auto& row : mTable)
			{
				for (auto& column : row)
				{
					target.draw(column);
				}
			}
		}
	
		void UpdateCellule()
		{
			mCelluleHeight = mShape.getSize().y / (float)mTable.size();

			float x = mShape.getPosition().x;
			float y = mShape.getPosition().y;

			for (auto& row : mTable)
			{	
				x = mShape.getPosition().x;
				for (auto& column : row)
				{
					column.SetSize(sf::Vector2f(mCelluleWidth, mCelluleHeight));
					column.SetPosition(sf::Vector2f(x, y));
					column.CenterText(mLabel);
					x += mCelluleWidth;
				}
				y += mCelluleHeight;
			}
		}
	};
}